// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueSpeakerComponent.h"
#include "DialogueSpeakerSocket.h"
#include "Events/DialogueEventBase.h"
#include "Nodes/DialogueSpeechNode.h"
#include "DialoguePlayerBlockMovementEvent.generated.h"

class UDialogueSpeakerSocket;

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class GAMEOFF2024_API UDialoguePlayerBlockMovementEvent : public UDialogueEventBase
{
	GENERATED_BODY()

public:
	/** UDialogueEventBase Impl. */
	virtual void PlayEvent() override;
	virtual bool HasAllRequirements() const override;
	virtual FText GetGraphDescription_Implementation() const override;
	/** End UDialogueEventBase */

	UFUNCTION(BlueprintNativeEvent)
	bool IsValidEvent() const;
	virtual bool IsValidEvent_Implementation() const;

	UFUNCTION(BlueprintCallable, Category="Dialogue")
	FSpeechDetails GetCurrentSpeechDetails() const;

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Dialogue")
	void OnPlayEvent(const FSpeakerActorEntry& InPlayerEntry);

	virtual void OnPlayEvent_Implementation(const FSpeakerActorEntry& InPlayerEntry)
	{
	};

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogueEvent", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDialogueSpeakerSocket> Player;

	UPROPERTY(EditAnywhere, Category = "DialogueEvent")
	bool bBlockMovementInput;

	UPROPERTY(EditAnywhere, Category = "DialogueEvent")
	bool bBlockLookInput;

	UPROPERTY(EditAnywhere, Category = "DialogueEvent")
	bool bBlockMenuInput;
};
