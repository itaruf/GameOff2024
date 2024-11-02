// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PlayerCharacterHelpers.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF2024_API UPlayerCharacterHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerCharacterHelpers", meta = (WorldContext = "WorldContextObject"))
	static FName GetPlayerCharacterName(const UObject* WorldContextObject, const int PlayerIndex);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerCharacterHelpers", meta = (WorldContext = "WorldContextObject"))
	static ACharacter* GetPlayerCharacterFromPlayerController(const UObject* WorldContextObject, const int PlayerIndex);
};
