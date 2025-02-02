// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueQuestQuery.h"

#include "DialogueSpeakerComponent.h"
#include "DialogueSpeakerSocket.h"
#include "Kismet/GameplayStatics.h"

const UGameInstance* UDialogueQuestQuery::GetGameInstance()
{
	const UWorld* World = Target->GetSpeakerComponent(GetDialogue())->GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance: World is nullptr"));
		return nullptr;
	}

	return Cast<UGameInstance>(UGameplayStatics::GetGameInstance(World));
}
