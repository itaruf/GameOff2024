// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameOff2024GameMode.h"
#include "GameOff2024Character.h"
#include "UObject/ConstructorHelpers.h"

AGameOff2024GameMode::AGameOff2024GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
