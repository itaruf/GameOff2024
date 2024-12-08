// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/IDialogueProvider.h"
#include "Interfaces/IInteractProvider.h"
#include "Logging/LogMacros.h"
#include "GameOff2024Character.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AGameOff2024Character : public ACharacter, public IDialogueProvider, public IInteractProvider
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;


	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	AGameOff2024Character();

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	bool bCanJumpDuringDialogue;

	UPROPERTY(BlueprintReadWrite, Category = "Components|Dialogue")
	UDialogueSpeakerComponent* DialogueSpeakerComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Components|Interact")
	UInteractComponent* InteractComponent;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Input, DisplayName = "Can Jump During Dialogue")
	FORCEINLINE bool CanJumpDuringDialogue() const { return bCanJumpDuringDialogue; }

	UFUNCTION(BlueprintCallable, Category = Input, DisplayName = "Set Can Jump During Dialogue")
	FORCEINLINE void SetCanJumpDuringDialogue(const bool bNewCanJumpDuringDialogue)
	{
		bCanJumpDuringDialogue = bNewCanJumpDuringDialogue;
	}

	virtual bool CanJumpInternal_Implementation() const override;

	UFUNCTION(BlueprintCallable, Category = "Dialogue", DisplayName = "Get Dialogue Speaker Component")
	FORCEINLINE UDialogueSpeakerComponent* GetDialogueSpeakerComponent_Implementation() const override
	{
		return DialogueSpeakerComponent;
	}

	UFUNCTION(BlueprintCallable, Category = "Interact", DisplayName = "Get Interact Component")
	FORCEINLINE UInteractComponent* GetInteractComponent_Implementation() const override { return InteractComponent; }
};
