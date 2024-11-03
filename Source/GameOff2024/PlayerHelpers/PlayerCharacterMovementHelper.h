// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PlayerCharacterMovementHelper.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF2024_API UPlayerCharacterMovementHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerMovementHelpers", meta = (WorldContext = "WorldContextObject"), DisplayName = "Get Player Character Movement Component")
	static UCharacterMovementComponent* GetPlayerCharacterMovementComponent(UObject* WorldContextObject, const int PlayerIndex = 0);
};
