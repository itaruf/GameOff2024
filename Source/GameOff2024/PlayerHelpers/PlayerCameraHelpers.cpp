// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCameraHelpers.h"
#include "PlayerCharacterHelpers.h"
#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"
#include "Math/Transform.h"

UCameraComponent* UPlayerCameraHelpers::GetPlayerCameraComponent(const UObject* WorldContextObject, const int PlayerIndex)
{
	const ACharacter* PlayerCharacter = UPlayerCharacterHelpers::GetPlayerCharacterFromPlayerController(WorldContextObject, PlayerIndex);
	return PlayerCharacter ? PlayerCharacter->FindComponentByClass<UCameraComponent>() : nullptr;
}

TArray<UCameraComponent*> UPlayerCameraHelpers::GetPlayerCameraComponents(const UObject* WorldContextObject, const int PlayerIndex)
{
	TArray<UCameraComponent*> CameraComponents;
	if (const ACharacter* PlayerCharacter = UPlayerCharacterHelpers::GetPlayerCharacterFromPlayerController(WorldContextObject, PlayerIndex))
	{
		PlayerCharacter->GetComponents<UCameraComponent>(CameraComponents);
	}
	return CameraComponents;
}

UCameraComponent* UPlayerCameraHelpers::GetPlayerCameraComponentByTag(const UObject* WorldContextObject, const FName Tag, const int PlayerIndex)
{
	const ACharacter* PlayerCharacter = UPlayerCharacterHelpers::GetPlayerCharacterFromPlayerController(WorldContextObject, PlayerIndex);
	return PlayerCharacter ? PlayerCharacter->FindComponentByTag<UCameraComponent>(Tag) : nullptr;
}

TArray<UActorComponent*> UPlayerCameraHelpers::GetPlayerCameraComponentsByTag(const UObject* WorldContextObject, const FName Tag, const int PlayerIndex)
{
	TArray<UActorComponent*> CameraComponents;
	if (const ACharacter* PlayerCharacter = UPlayerCharacterHelpers::GetPlayerCharacterFromPlayerController(WorldContextObject, PlayerIndex))
	{
		CameraComponents = PlayerCharacter->GetComponentsByTag(UCameraComponent::StaticClass(), Tag);
	}
	return CameraComponents;
}

FVector UPlayerCameraHelpers::GetPlayerCameraRelativeLocation(const UObject* WorldContextObject, const int PlayerIndex)
{
	const UCameraComponent* CameraComponent = GetPlayerCameraComponent(WorldContextObject, PlayerIndex);
	return CameraComponent ? CameraComponent->GetRelativeLocation() : FVector::ZeroVector;
}

FVector UPlayerCameraHelpers::GetPlayerCameraRelativeLocationByTag(const UObject* WorldContextObject, const FName Tag, const int PlayerIndex)
{
	const UCameraComponent* CameraComponent = GetPlayerCameraComponentByTag(WorldContextObject, Tag, PlayerIndex);
	return CameraComponent ? CameraComponent->GetRelativeLocation() : FVector::ZeroVector;
}

FVector UPlayerCameraHelpers::GetPlayerCameraWorldLocation(const UObject* WorldContextObject, const int PlayerIndex)
{
	const UCameraComponent* CameraComponent = GetPlayerCameraComponent(WorldContextObject, PlayerIndex);
	return CameraComponent ? CameraComponent->GetComponentTransform().GetLocation() : FVector::ZeroVector;
}

FVector UPlayerCameraHelpers::GetPlayerCameraWorldLocationByTag(const UObject* WorldContextObject, const FName Tag, const int PlayerIndex)
{
	const UCameraComponent* CameraComponent = GetPlayerCameraComponentByTag(WorldContextObject, Tag, PlayerIndex);
	return CameraComponent ? CameraComponent->GetComponentTransform().GetLocation() : FVector::ZeroVector;
}
