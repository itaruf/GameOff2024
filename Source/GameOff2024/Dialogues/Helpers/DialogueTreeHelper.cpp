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

	// Ensure GetEdGraph() is valid before accessing Nodes
	UEdGraph* EdGraph = Dialogue->GetEdGraph();
	if (!EdGraph)
	{
		UE_LOG(LogTemp, Error, TEXT("Dialogue's EdGraph is null."));
		return nullptr;
	}

	auto& Nodes = EdGraph->Nodes;
	for (auto& Node : Nodes)
	{
		if (!Node) // Ensure the Node is valid before using it
		{
			UE_LOG(LogTemp, Warning, TEXT("Encountered a null node in the dialogue graph."));
			continue;
		}

		if (Node->GetNodeTitle(ENodeTitle
			Type::Type::FullTitle).ToString() == NodeName.ToString())
		{
			UE_LOG(LogTemp, Warning, TEXT("Node %s found"), *NodeName.ToString());
			return Cast<UDialogueNode>(Node); // Return the found node instead of nullptr
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Node %s not found in the dialogue graph."), *NodeName.ToString());
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
