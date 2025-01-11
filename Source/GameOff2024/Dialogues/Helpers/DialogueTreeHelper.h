// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Nodes/DialogueNode.h"
#include "DialogueTreeHelper.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFF2024_API UDialogueTreeHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "DialogueTreeHelper", meta = (WorldContext = "WorldContextObject"))
	static UDialogueNode* GetNode(const UObject* WorldContextObject, const UDialogue* Dialogue, const FName NodeID);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "DialogueTreeHelper", meta = (WorldContext = "WorldContextObject"))
	static bool HasNode(const UObject* WorldContextObject, const UDialogue* Dialogue, const FName NodeID);
};
