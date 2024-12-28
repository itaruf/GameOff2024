// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//UE
#include "Events/DialogueEventBase.h"
//Plugin
#include "DialogueSpeakerComponent.h"
#include "SpeechDetails.h"

#include "DialogueStartEvent.generated.h"

class UDialogue;
class UDialogueSpeakerSocket;
/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class GAMEOFF2024_API UDialogueStartEvent : public UDialogueEventBase
{
	GENERATED_BODY()

public:
	/** UDialogueEventBase Impl. */
	virtual void PlayEvent() override;
	virtual bool HasAllRequirements() const override;
	virtual FText GetGraphDescription_Implementation() const override;
	/** End UDialogueEventBase */
	
	/**
	* Checks if the event is valid and has all of the information it needs
	* to compile.
	*
	* @return bool - True if all requisite data is present; false otherwise.
	*/
	UFUNCTION(BlueprintNativeEvent)
	bool IsValidEvent() const;
	virtual bool IsValidEvent_Implementation() const;

	/**
	* Retrieves the speech details for the speech this event was 
	* called from. If not called from a speech, retrieves an empty 
	* speech details struct.
	* 
	* @param InDetails - FSpeechDetails, the new speech details. 
	*/
	UFUNCTION(BlueprintCallable, Category="Dialogue")
	const FSpeechDetails GetCurrentSpeechDetails() const;

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Dialogue")
	void OnPlayEvent(const TArray< FSpeakerActorEntry>& Speakers);
	virtual void OnPlayEvent_Implementation(const TArray<FSpeakerActorEntry>& Speakers) {};

protected:
	/** Speakers to attach to the event */
	UPROPERTY(EditAnywhere, Category = "DialogueEvent")
	TArray<TObjectPtr<UDialogueSpeakerSocket>> Targets;
};
