// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteractProvider.generated.h"

class UInteractComponent;
// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UInteractProvider : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEOFF2024_API IInteractProvider
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact", DisplayName = "Get Interact Component")
	UInteractComponent* GetInteractComponent() const;
};
