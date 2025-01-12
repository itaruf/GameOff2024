// Copyright Zachary Brett, 2024. All rights reserved.

//Header
#include "DialogueNoParamQueryBool.h"
//Plugin

bool UDialogueNoParamQueryBool::ExecuteQuery()
{
	//Query the speaker
	return QuerySpeaker();
}

bool UDialogueNoParamQueryBool::IsValidQuery() const
{
	return IsValidSpeakerQuery();
}


bool UDialogueNoParamQueryBool::IsValidSpeakerQuery_Implementation() const
{
	return true;
}
