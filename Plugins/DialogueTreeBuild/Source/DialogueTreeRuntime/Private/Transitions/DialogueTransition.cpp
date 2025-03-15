// Copyright Zachary Brett, 2024. All rights reserved.

//Header
#include "Transitions/DialogueTransition.h"
//UE
#include "Engine/World.h"
//Plugin
#include "Dialogue.h"
#include "DialogueConnectionLimit.h"
#include "DialogueSpeakerComponent.h"
#include "Nodes/DialogueNode.h"
#include "Nodes/DialogueSpeechNode.h"
#include "LogDialogueTree.h"

UDialogueTransition::UDialogueTransition()
{
	OnContentEnd.BindUFunction(this, "OnDonePlayingContent");
	OnTimerEnd.BindUFunction(this, "OnMinPlayTimeElapsed");
}

void UDialogueTransition::SetOwningNode(UDialogueSpeechNode* InNode)
{
	OwningNode = InNode;
}

void UDialogueTransition::StartTransition()
{
	// Reset the skip flag and other state variables.
	bHasBeenSkipped = false;
	bMinPlayTimeElapsed = false;
	bAudioFinished = false;

	// Verify owning node exists...
	if (!OwningNode)
	{
		UE_LOG(
			LogDialogueTree,
			Error,
			TEXT("Transition failed to find owning node. Ending dialogue early."));
		OwningNode->GetDialogue()->EndDialogue();
		return;
	}

	// Get speaker...
	UDialogueSpeakerComponent* Speaker = OwningNode->GetSpeaker();
	if (!Speaker)
	{
		UE_LOG(
			LogDialogueTree,
			Error,
			TEXT("Transition failed to find speaker component. Ending dialogue early."));
		OwningNode->GetDialogue()->EndDialogue();
		return;
	}

	// Set timer for minimum play time
	float MinPlayTime = OwningNode->GetDetails().MinimumPlayTime;
	if (MinPlayTime > 0.01f)
	{
		Speaker->GetWorld()->GetTimerManager().SetTimer(
			MinPlayTimeHandle,
			OnTimerEnd,
			MinPlayTime,
			false
		);
	}
	else
	{
		bMinPlayTimeElapsed = true;
	}

	// Start listening for audio finish
	if (Speaker->IsPlaying())
	{
		Speaker->OnAudioFinished.AddUnique(OnContentEnd);
	}
	else
	{
		bAudioFinished = true;
	}

	// If conditions are already met, transition out immediately.
	if (bMinPlayTimeElapsed && bAudioFinished)
	{
		TransitionOut();
	}
}

void UDialogueTransition::Skip()
{
	// Mark that skip has been triggered.
	bHasBeenSkipped = true;

	// Cancel the auto-input timer if it's active.
	if (OwningNode)
	{
		UWorld* World = OwningNode->GetWorld();
		if (World && World->GetTimerManager().IsTimerActive(MinPlayTimeHandle))
		{
			World->GetTimerManager().ClearTimer(MinPlayTimeHandle);
		}
	}

	// Force the minimum play time condition to be met.
	bMinPlayTimeElapsed = true;

	// If the audio hasn't finished, force it to complete.
	if (!bAudioFinished)
	{
		OnDonePlayingContent();
	}

	// Let the speaker know we are skipping its speech.
	if (OwningNode && OwningNode->GetSpeaker())
	{
		OwningNode->GetSpeaker()->BroadcastSpeechSkipped(OwningNode->GetDetails());
	}

	// Immediately transition out.
	TransitionOut();
}

FText UDialogueTransition::GetDisplayName() const
{
	return FText::FromString(StaticClass()->GetName());
}

FText UDialogueTransition::GetNodeCreationTooltip() const
{
	return FText::GetEmpty();
}

EDialogueConnectionLimit UDialogueTransition::GetConnectionLimit() const
{
	return EDialogueConnectionLimit::Single;
}

void UDialogueTransition::CheckTransitionConditions()
{
	if (bAudioFinished && bMinPlayTimeElapsed && !OwningNode->GetIsBlocking())
	{
		TransitionOut();
	}
}

void UDialogueTransition::OnDonePlayingContent()
{
	if (bHasBeenSkipped)
	{
		return; // Skip further processing if we've already skipped.
	}

	//Unbind from audio event 
	UDialogueSpeakerComponent* Speaker = OwningNode->GetSpeaker();

	if (Speaker)
	{
		Speaker->Stop();
		Speaker->OnAudioFinished.Remove(OnContentEnd);
	}

	//Mark audio complete
	bAudioFinished = true;

	//See if we should transition out
	CheckTransitionConditions();
}

void UDialogueTransition::OnMinPlayTimeElapsed()
{
	if (bHasBeenSkipped)
	{
		return; // Exit if already skipped.
	}

	//Mark min play time elapsed
	bMinPlayTimeElapsed = true;

	//Check if we should transition out
	CheckTransitionConditions();
}
