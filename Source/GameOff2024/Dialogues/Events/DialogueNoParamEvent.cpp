// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogueNoParamEvent.h"

//Unreal
#include "Engine/World.h"
//Plugin
#include "Dialogue.h"

void UDialogueNoParamEvent::PlayEvent()
{
	bBlocking = false;
	
	OnPlayEvent();
}

bool UDialogueNoParamEvent::HasAllRequirements() const
{
	if (!IsValidEvent())
		return false;
	
	return true;
}

FText UDialogueNoParamEvent::GetGraphDescription_Implementation() const
{
	return FText::FromString(GetClass()->GetName());
}

bool UDialogueNoParamEvent::IsValidEvent_Implementation() const
{
	return true;
}

const FSpeechDetails UDialogueNoParamEvent::GetCurrentSpeechDetails() const
{
	if (UDialogueSpeechNode* Speech =
		GetTypedOuter<UDialogueSpeechNode>())
	{
		return Speech->GetDetails();
	}

	return FSpeechDetails();
}
