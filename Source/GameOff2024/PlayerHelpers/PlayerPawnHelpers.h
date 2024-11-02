// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PlayerPawnHelpers.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF2024_API UPlayerPawnHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerPawnHelpers", meta = (WorldContext = "WorldContextObject"))
	static FName GetPlayerPawnName(const UObject* WorldContextObject, const int PlayerIndex);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerCharacterHelpers", meta = (WorldContext = "WorldContextObject"))
	static APawn* GetPlayerPawnFromGameMode(const UObject* WorldContextObject);
};
