// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PlayerCameraHelpers.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF2024_API UPlayerCameraHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerCameraHelpers", meta = (WorldContext = "WorldContextObject"))
	static UCameraComponent* GetPlayerCameraComponent(const UObject* WorldContextObject, const int PlayerIndex = 0);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerCameraHelpers", meta = (WorldContext = "WorldContextObject"))
	static TArray<UCameraComponent*> GetPlayerCameraComponents(const UObject* WorldContextObject, const int PlayerIndex = 0);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerCameraHelpers", meta = (WorldContext = "WorldContextObject"))
	static UCameraComponent* GetPlayerCameraComponentByTag(const UObject* WorldContextObject, const FName Tag, int PlayerIndex = 0);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerCameraHelpers", meta = (WorldContext = "WorldContextObject"))
	static TArray<UActorComponent*> GetPlayerCameraComponentsByTag(const UObject* WorldContextObject, const FName Tag, const int PlayerIndex = 0);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerCameraHelpers", meta = (WorldContext = "WorldContextObject"))
	static FVector GetPlayerCameraRelativeLocation(const UObject* WorldContextObject, const int PlayerIndex = 0);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerCameraHelpers", meta = (WorldContext = "WorldContextObject"))
	static FVector GetPlayerCameraRelativeLocationByTag(const UObject* WorldContextObject, const FName Tag, const int PlayerIndex = 0);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerCameraHelpers", meta = (WorldContext = "WorldContextObject"))
	static FVector GetPlayerCameraWorldLocation(const UObject* WorldContextObject, const int PlayerIndex = 0);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerCameraHelpers", meta = (WorldContext = "WorldContextObject"))
	static FVector GetPlayerCameraWorldLocationByTag(const UObject* WorldContextObject, const FName Tag, const int PlayerIndex = 0);
};
