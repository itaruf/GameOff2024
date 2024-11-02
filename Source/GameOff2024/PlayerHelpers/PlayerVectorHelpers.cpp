// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerVectorHelpers.h"

#include "PlayerCharacterHelpers.h"
#include "GameFramework/Character.h"

FVector UPlayerVectorHelpers::GetPlayerForwardVector(const UObject* WorldContextObject, const int PlayerIndex)
{
	const ACharacter* PlayerCharacter = UPlayerCharacterHelpers::GetPlayerCharacterFromPlayerController(WorldContextObject, PlayerIndex);
	return PlayerCharacter ? PlayerCharacter->GetActorForwardVector() : FVector::ForwardVector;
}

FVector UPlayerVectorHelpers::GetPlayerBackwardVector(const UObject* WorldContextObject, const int PlayerIndex)
{
	return GetPlayerForwardVector(WorldContextObject, PlayerIndex) * -1.f;
}

FVector UPlayerVectorHelpers::GetPlayerUpVector(const UObject* WorldContextObject, const int PlayerIndex)
{
	const ACharacter* PlayerCharacter = UPlayerCharacterHelpers::GetPlayerCharacterFromPlayerController(WorldContextObject, PlayerIndex);
	return PlayerCharacter ? PlayerCharacter->GetActorUpVector() : FVector::UpVector;
}

FVector UPlayerVectorHelpers::GetPlayerDownVector(const UObject* WorldContextObject, const int PlayerIndex)
{
	return GetPlayerUpVector(WorldContextObject, PlayerIndex) * -1.f;
}

FVector UPlayerVectorHelpers::GetPlayerRightVector(const UObject* WorldContextObject, const int PlayerIndex)
{
	const ACharacter* PlayerCharacter = UPlayerCharacterHelpers::GetPlayerCharacterFromPlayerController(WorldContextObject, PlayerIndex);
	return PlayerCharacter ? PlayerCharacter->GetActorRightVector() : FVector::RightVector;
}

FVector UPlayerVectorHelpers::GetPlayerLeftVector(const UObject* WorldContextObject, const int PlayerIndex)
{
	return GetPlayerRightVector(WorldContextObject, PlayerIndex) * -1.f;
}
