// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PlayerTransformHelpers.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF2024_API UPlayerTransformHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerHelpers", meta = (WorldContext = "WorldContextObject"))
	static FVector GetPlayerLocation(const UObject* WorldContextObject, const int PlayerIndex = 0);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerHelpers", meta = (WorldContext = "WorldContextObject"))
	static FRotator GetPlayerRotation(const UObject* WorldContextObject, int PlayerIndex = 0);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerHelpers", meta = (WorldContext = "WorldContextObject"))
	static FVector GetPlayerScale(const UObject* WorldContextObject, int PlayerIndex = 0);
	UFUNCTION(BlueprintCallable, Category = "PlayerHelpers", meta = (WorldContext = "WorldContextObject"))
	static FQuat GetPlayerRotationQuat(const UObject* WorldContextObject, int PlayerIndex);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerHelpers", meta = (WorldContext = "WorldContextObject"))
	static FVector GetPlayerSocketLocation(const UObject* WorldContextObject, const USceneComponent* Target, const FName& SocketName, const int PlayerIndex = 0);
};