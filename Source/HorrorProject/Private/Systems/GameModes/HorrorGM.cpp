// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/GameModes/HorrorGM.h"
#include "Characters/HorrorCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHorrorGM::AHorrorGM()
	: Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/HorrorGame/Characters/Player/BP_HorrorCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}
