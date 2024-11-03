// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterMovementHelper.h"

#include "PlayerCharacterHelpers.h"
#include "GameFramework/Character.h"

UCharacterMovementComponent* UPlayerCharacterMovementHelper::GetPlayerCharacterMovementComponent(UObject* WorldContextObject, const int PlayerIndex)
{
	const ACharacter* PlayerCharacter = UPlayerCharacterHelpers::GetPlayerCharacterFromPlayerController(
		WorldContextObject, PlayerIndex);
	return PlayerCharacter ? PlayerCharacter->FindComponentByClass<UCharacterMovementComponent>() : nullptr;
}
