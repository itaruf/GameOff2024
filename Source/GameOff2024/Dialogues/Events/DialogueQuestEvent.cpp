// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogueQuestEvent.h"

#include "Engine/World.h"
#include "Dialogue.h"
#include "DialogueSpeakerComponent.h"
#include "DialogueSpeakerSocket.h"
#include "Kismet/GameplayStatics.h"

void UDialogueQuestEvent::PlayEvent()
{
	bBlocking = false;

	OnPlayEvent();
}

bool UDialogueQuestEvent::HasAllRequirements() const
{
	if (!IsValidEvent())
		return false;

	if (!Target)
		return false;


	return true;
}

FText UDialogueQuestEvent::GetGraphDescription_Implementation() const
{
	return FText::FromString(GetClass()->GetName());
}

bool UDialogueQuestEvent::IsValidEvent_Implementation() const
{
	return true;
}

const FSpeechDetails UDialogueQuestEvent::GetCurrentSpeechDetails() const
{
	if (UDialogueSpeechNode* Speech =
		GetTypedOuter<UDialogueSpeechNode>())
	{
		return Speech->GetDetails();
	}

	return FSpeechDetails();
}

const UGameInstance* UDialogueQuestEvent::GetGameInstance()
{
	const UWorld* World = Target->GetSpeakerComponent(Dialogue)->GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance: World is nullptr"));
		return nullptr;
	}

	return Cast<UGameInstance>(UGameplayStatics::GetGameInstance(World));
}
