// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "UMGProject.h"
#include "UMGProjectGameMode.h"
#include "UMGProjectCharacter.h"

AUMGProjectGameMode::AUMGProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/Blueprints/ThirdPersonCharacter.ThirdPersonCharacter'"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}
