// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IDialogueProvider.generated.h"

class UDialogueSpeakerComponent;
// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UDialogueProvider : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEOFF2024_API IDialogueProvider
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Dialogue", DisplayName = "Get Dialogue Speaker Component")
	UDialogueSpeakerComponent* GetDialogueSpeakerComponent() const;
};
