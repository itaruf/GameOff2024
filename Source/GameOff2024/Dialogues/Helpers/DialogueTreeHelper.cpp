// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueTreeHelper.h"

#include "Dialogue.h"

UDialogueNode* UDialogueTreeHelper::GetNode(const UObject* WorldContextObject, const UDialogue* Dialogue,
                                            const FName NodeName)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
	{
		return nullptr;
	}

	if (!Dialogue)
	{
		return nullptr;
	}

	auto& Nodes = Dialogue->GetEdGraph()->Nodes;
	for (auto& Node : Nodes)
	{
		if (Node->GetNodeTitle(ENodeTitleType::Type::FullTitle).ToString() == NodeName.ToString())
		{
			UE_LOG(LogTemp, Warning, TEXT("Node %s found"), *NodeName.ToString());
			return nullptr;
		}
	}

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
