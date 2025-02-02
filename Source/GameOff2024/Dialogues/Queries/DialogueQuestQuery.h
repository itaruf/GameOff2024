// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNoParamQueryBool.h"
#include "DialogueQuestQuery.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class GAMEOFF2024_API UDialogueQuestQuery : public UDialogueNoParamQueryBool
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Dialogue")
	const UGameInstance* GetGameInstance();

protected:
	/** Speakers to attach to the event */
	UPROPERTY(EditAnywhere, Category = "DialogueEvent")
	TObjectPtr<UDialogueSpeakerSocket> Target;
};
