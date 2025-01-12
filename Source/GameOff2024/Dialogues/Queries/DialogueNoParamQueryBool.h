// Copyright Zachary Brett, 2024. All rights reserved.

#pragma once

//UE
#include "CoreMinimal.h"
//Plugin
#include "Conditionals/Queries/Base/DialogueQueryBool.h"
//Generated
#include "DialogueNoParamQueryBool.generated.h"

class UDialogueSpeakerSocket;

/**
 * Abstract base class for dialogue queries that operate on a 
 * speaker component and return a bool value. 
 * Designed to be implemented by the user in blueprint. 
 */
UCLASS(Abstract, Blueprintable, EditInlineNew)
class GAMEOFF2024_API UDialogueNoParamQueryBool : public UDialogueQueryBool
{
	GENERATED_BODY()

public:
	/** IDialogueQueryFloat Impl. */
	virtual bool ExecuteQuery() override;
	virtual bool IsValidQuery() const override;
	/** End IDialogueQueryFloat */

	/**
	* User specified query. Implemented via blueprint.
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Dialogue")
	bool QuerySpeaker() const;
	
	/**
	* User defineable function to check if the query is valid.
	*
	* @return bool - True if valid according to terms user sets. False
	* otherwise.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "Dialogue")
	bool IsValidSpeakerQuery() const;
	virtual bool IsValidSpeakerQuery_Implementation() const;
};
