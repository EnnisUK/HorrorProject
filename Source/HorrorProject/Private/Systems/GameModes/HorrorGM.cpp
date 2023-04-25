// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/GameModes/HorrorGM.h"
#include "Characters/PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHorrorGM::AHorrorGM()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/HorrorGame/Character/Player/BP_PlayerCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;


}
