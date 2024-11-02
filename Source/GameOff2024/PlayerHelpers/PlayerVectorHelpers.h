// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PlayerVectorHelpers.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF2024_API UPlayerVectorHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Return the Player's forward vector starting from their center  
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerVectorHelpers", meta = (WorldContext = "WorldContextObject"))
	static FVector GetPlayerForwardVector(const UObject* WorldContextObject, const int PlayerIndex = 0);
	// Return the Player's backward vector starting from their center  
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerVectorHelpers", meta = (WorldContext = "WorldContextObject"))
	static FVector GetPlayerBackwardVector(const UObject* WorldContextObject, const int PlayerIndex = 0);
	// Return the Player's up vector starting from their center  
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerVectorHelpers", meta = (WorldContext = "WorldContextObject"))
	static FVector GetPlayerUpVector(const UObject* WorldContextObject, const int PlayerIndex = 0);
	// Return the Player's down vector starting from their center  
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerVectorHelpers", meta = (WorldContext = "WorldContextObject"))
	static FVector GetPlayerDownVector(const UObject* WorldContextObject, const int PlayerIndex = 0);
	// Return the Player's right vector starting from their center  
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerVectorHelpers", meta = (WorldContext = "WorldContextObject"))
	static FVector GetPlayerRightVector(const UObject* WorldContextObject, const int PlayerIndex = 0);
	// Return the Player's left vector starting from their center  
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerVectorHelpers", meta = (WorldContext = "WorldContextObject"))
	static FVector GetPlayerLeftVector(const UObject* WorldContextObject, const int PlayerIndex = 0);
};
