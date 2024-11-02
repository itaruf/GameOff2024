// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCollisionHelper.h"

#include "PlayerCharacterHelpers.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"

UCapsuleComponent* UPlayerCollisionHelper::GetPlayerCapsuleComponent(const UObject* WorldContextObject, const int PlayerIndex)
{
	const ACharacter* PlayerCharacter = UPlayerCharacterHelpers::GetPlayerCharacterFromPlayerController(WorldContextObject, PlayerIndex);
	return PlayerCharacter ? PlayerCharacter->FindComponentByClass<UCapsuleComponent>(): nullptr;
}

UBoxComponent* UPlayerCollisionHelper::GetPlayerBoxComponent(const UObject* WorldContextObject, const int PlayerIndex)
{
	const ACharacter* PlayerCharacter = UPlayerCharacterHelpers::GetPlayerCharacterFromPlayerController(WorldContextObject, PlayerIndex);
	return PlayerCharacter ? PlayerCharacter->FindComponentByClass<UBoxComponent>(): nullptr;
}

USphereComponent* UPlayerCollisionHelper::GetPlayerSphereComponent(const UObject* WorldContextObject, const int PlayerIndex)
{
	const ACharacter* PlayerCharacter = UPlayerCharacterHelpers::GetPlayerCharacterFromPlayerController(WorldContextObject, PlayerIndex);
	return PlayerCharacter ? PlayerCharacter->FindComponentByClass<USphereComponent>(): nullptr;
}

FVector UPlayerCollisionHelper::GetPlayerShapeComponentLocation(const UObject* WorldContextObject, const TSubclassOf<UShapeComponent> ComponentClass, const int PlayerIndex)
{
	if (const ACharacter* PlayerCharacter = UPlayerCharacterHelpers::GetPlayerCharacterFromPlayerController(WorldContextObject, PlayerIndex))
	{
		if (const UShapeComponent* ShapeComponent = static_cast<UShapeComponent*>(PlayerCharacter->FindComponentByClass(ComponentClass)))
		{
			return ShapeComponent ?ShapeComponent->GetComponentLocation() : FVector::ZeroVector;
		}
	}
	return FVector::ZeroVector;
}
