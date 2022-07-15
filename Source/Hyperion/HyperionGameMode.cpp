// Copyright Epic Games, Inc. All Rights Reserved.

#include "HyperionGameMode.h"
#include "HyperionCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHyperionGameMode::AHyperionGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
