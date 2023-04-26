// Copyright Epic Games, Inc. All Rights Reserved.

#include "HorrorProjectGameMode.h"
#include "HorrorProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHorrorProjectGameMode::AHorrorProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/HorrorGame/Characters/Player/BP_HorrorCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
