// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueTreeHelper.h"

#include "Dialogue.h"

UDialogueNode* UDialogueTreeHelper::GetNode(const UObject* WorldContextObject, const UDialogue* Dialogue, const FName NodeName)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("WorldContextObject is invalid or has no world."));
		return nullptr;
	}

	if (!Dialogue)
	{
		UE_LOG(LogTemp, Error, TEXT("Dialogue is null."));
		return nullptr;
	}

	// Use runtime-accessible node storage instead of UEdGraph
	UDialogueNode* FoundNode = Dialogue->GetRuntimeNode(NodeName);
	if (FoundNode)
	{
		UE_LOG(LogTemp, Warning, TEXT("Node %s found"), *NodeName.ToString());
		return FoundNode;
	}

	UE_LOG(LogTemp, Warning, TEXT("Node %s not found."), *NodeName.ToString());
	return nullptr;
}


bool UDialogueTreeHelper::HasNode(const UObject* WorldContextObject, const UDialogue* Dialogue, const FName NodeID)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
	{
		return false;
	}

	if (!Dialogue)
	{
		return false;
	}

	return Dialogue->HasNode(NodeID);
}
