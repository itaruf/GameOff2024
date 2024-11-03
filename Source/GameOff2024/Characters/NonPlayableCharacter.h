// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NonPlayableCharacter.generated.h"

UCLASS()
class GAMEOFF2024_API ANonPlayableCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANonPlayableCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC", meta = (AllowPrivateAccess = "true"))
	FName Name;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "NPC", DisplayName = "Get Name")
	FORCEINLINE FName GetName() const
	{
		return Name;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "NPC", DisplayName = "Set Name")
	FORCEINLINE void SetName(const FName& NewName)
	{
		Name = NewName;
	}

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
