// Fill out your copyright notice in the Description page of Project Settings.

#include "DialoguePlayerBlockMovementEvent.h"

void UDialoguePlayerBlockMovementEvent::PlayEvent()
{
	bBlocking = false;

	if (UDialogueSpeakerComponent* PlayerSpeakerComponent = Player->GetSpeakerComponent(Dialogue))
	{
		const FSpeakerActorEntry PlayerSocketEntry =
			PlayerSpeakerComponent->ToSpeakerActorEntry();
		
		OnPlayEvent(PlayerSocketEntry);
	}
}

bool UDialoguePlayerBlockMovementEvent::HasAllRequirements() const
{
	if (!IsValidEvent())
		return false;
	
	return true;
}

FText UDialoguePlayerBlockMovementEvent::GetGraphDescription_Implementation() const
{
	return FText::FromString(GetClass()->GetName());
}

bool UDialoguePlayerBlockMovementEvent::IsValidEvent_Implementation() const
{
	return true;
}

FSpeechDetails UDialoguePlayerBlockMovementEvent::GetCurrentSpeechDetails() const
{
	if (UDialogueSpeechNode* Speech =
		GetTypedOuter<UDialogueSpeechNode>())
	{
		return Speech->GetDetails();
	}

	return FSpeechDetails();
}
