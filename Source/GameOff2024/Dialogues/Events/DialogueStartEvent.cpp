// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogueStartEvent.h"

#include "Engine/World.h"
#include "Dialogue.h"
#include "DialogueSpeakerComponent.h"
#include "DialogueSpeakerSocket.h"

void UDialogueStartEvent::PlayEvent()
{
	bBlocking = false;

	TArray<FSpeakerActorEntry> TargetsEntries;
	for (UDialogueSpeakerSocket* Socket : Targets)
	{
		UDialogueSpeakerComponent* SocketComponent =
			Socket->GetSpeakerComponent(Dialogue);
		if (SocketComponent)
		{
			// UE_LOG(
			// 	LogDialogueTree,
			// 	Warning,
			// 	TEXT(
			// 		"Failed to play event because the target speaker component was not supplied. Verify that the dialogue name property matches the speaker's role in the dialogue."
			// 	)
			// );
			// return;
		FSpeakerActorEntry SocketEntry =
			SocketComponent->ToSpeakerActorEntry();
		TargetsEntries.Add(SocketEntry);
		}

	}

	OnPlayEvent(TargetsEntries);
}

bool UDialogueStartEvent::HasAllRequirements() const
{
	if (!IsValidEvent())
		return false;

	for (auto& Target : Targets)
	{
		if (!Target)
			return false;
	}

	return true;
}

FText UDialogueStartEvent::GetGraphDescription_Implementation() const
{
	return FText::FromString(GetClass()->GetName());
}

bool UDialogueStartEvent::IsValidEvent_Implementation() const
{
	return true;
}

const FSpeechDetails UDialogueStartEvent::GetCurrentSpeechDetails() const
{
	if (UDialogueSpeechNode* Speech =
		GetTypedOuter<UDialogueSpeechNode>())
	{
		return Speech->GetDetails();
	}

	return FSpeechDetails();
}
