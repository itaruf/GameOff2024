// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PlayerCollisionHelper.generated.h"

class UCapsuleComponent;
class UBoxComponent;
class USphereComponent;
/**
 * 
 */
UCLASS()
class GAMEOFF2024_API UPlayerCollisionHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerCollisionHelper", meta = (WorldContext = "WorldContextObject"))
	static UCapsuleComponent* GetPlayerCapsuleComponent(const UObject* WorldContextObject, const int PlayerIndex);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerCollisionHelper", meta = (WorldContext = "WorldContextObject"))
	static UBoxComponent* GetPlayerBoxComponent(const UObject* WorldContextObject, const int PlayerIndex);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerCollisionHelper", meta = (WorldContext = "WorldContextObject"))
	static USphereComponent* GetPlayerSphereComponent(const UObject* WorldContextObject, const int PlayerIndex);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerCollisionHelper", meta = (WorldContext = "WorldContextObject"))
	static FVector GetPlayerShapeComponentLocation(const UObject* WorldContextObject, const TSubclassOf<UShapeComponent> ComponentClass = nullptr, const int PlayerIndex = 0);
};
