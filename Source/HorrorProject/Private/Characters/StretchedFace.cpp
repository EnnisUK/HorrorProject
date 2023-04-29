// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/StretchedFace.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"

// Sets default values
AStretchedFace::AStretchedFace()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStretchedFace::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStretchedFace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AStretchedFace::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


