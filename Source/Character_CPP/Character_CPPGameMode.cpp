// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Character_CPPGameMode.h"
#include "Character_CPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACharacter_CPPGameMode::ACharacter_CPPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
