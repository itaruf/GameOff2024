// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterHelpers.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

FName UPlayerCharacterHelpers::GetPlayerCharacterName(const UObject* WorldContextObject, const int PlayerIndex)
{
	if (const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, PlayerIndex))
	{
		if (const ACharacter* PlayerCharacter = PlayerController->GetCharacter())
		{
			return static_cast<FName>(PlayerCharacter->GetName());
		}
	}
	return NAME_None;
}

ACharacter* UPlayerCharacterHelpers::GetPlayerCharacterFromPlayerController(const UObject* WorldContextObject, const int PlayerIndex)
{
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, PlayerIndex);
	return PlayerController ? PlayerController->GetCharacter() : nullptr;
}
