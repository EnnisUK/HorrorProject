// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/RestingDesk.h"
#include "Camera/CameraComponent.h"


// Sets default values
ARestingDesk::ARestingDesk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Desk Component
	Desk = CreateDefaultSubobject<UStaticMeshComponent>("DeskMesh");

	// Create Chair Component
	Chair = CreateDefaultSubobject<UStaticMeshComponent>("ChairMesh");
	Chair->SetupAttachment(Desk);

	// Create Camera Component
	DeskCamera = CreateDefaultSubobject<UCameraComponent>("DeskCamera");
	DeskCamera->SetupAttachment(Desk);
}

// Called when the game starts or when spawned
void ARestingDesk::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARestingDesk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARestingDesk::InteractPure()
{
}

void ARestingDesk::SetDisplayName()
{
}

