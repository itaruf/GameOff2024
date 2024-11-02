// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnHelpers.h"

#include "Kismet/GameplayStatics.h"

FName UPlayerPawnHelpers::GetPlayerPawnName(const UObject* WorldContextObject, const int PlayerIndex)
{
	if (const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, PlayerIndex))
	{
		if (const APawn* PlayerPawn = PlayerController->GetPawn())
		{
			return static_cast<FName>(PlayerPawn->GetName());
		}
	}
	return NAME_None;
}

APawn* UPlayerPawnHelpers::GetPlayerPawnFromGameMode(const UObject* WorldContextObject)
{
	// TODO: complete this function according to the need of the project
	return nullptr;
}
