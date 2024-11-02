// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerTransformHelpers.h"

#include "PlayerCharacterHelpers.h"
#include "GameFramework/Character.h"

FVector UPlayerTransformHelpers::GetPlayerLocation(const UObject* WorldContextObject, const int PlayerIndex)
{
	const ACharacter* PlayerCharacter = UPlayerCharacterHelpers::GetPlayerCharacterFromPlayerController(WorldContextObject, PlayerIndex);
	return PlayerCharacter ? PlayerCharacter->GetActorLocation() : FVector::ZeroVector;
}

FRotator UPlayerTransformHelpers::GetPlayerRotation(const UObject* WorldContextObject, const int PlayerIndex)
{
	const ACharacter* PlayerCharacter = UPlayerCharacterHelpers::GetPlayerCharacterFromPlayerController(WorldContextObject, PlayerIndex);
	return PlayerCharacter ? PlayerCharacter->GetActorRotation() : FRotator::ZeroRotator;
}

FVector UPlayerTransformHelpers::GetPlayerScale(const UObject* WorldContextObject, const int PlayerIndex)
{
	const ACharacter* PlayerCharacter = UPlayerCharacterHelpers::GetPlayerCharacterFromPlayerController(WorldContextObject, PlayerIndex);
	return PlayerCharacter ? PlayerCharacter->GetActorScale() : FVector::ZeroVector;
}

FQuat UPlayerTransformHelpers::GetPlayerRotationQuat(const UObject* WorldContextObject, const int PlayerIndex)
{
	const ACharacter* PlayerCharacter = UPlayerCharacterHelpers::GetPlayerCharacterFromPlayerController(WorldContextObject, PlayerIndex);
	return PlayerCharacter ? PlayerCharacter->GetActorQuat() : FQuat::Identity;
}

FVector UPlayerTransformHelpers::GetPlayerSocketLocation(const UObject* WorldContextObject, const USceneComponent* Target, const FName& SocketName, const int PlayerIndex)
{
	return FVector::ZeroVector;
}
