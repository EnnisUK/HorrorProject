// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Door/DoorBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADoorBase::ADoorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>("DefualtSceneRoot");
	RootComponent = DefaultSceneRoot;

	Arrow = CreateDefaultSubobject<UArrowComponent>("RotationArrow");
	Arrow->SetupAttachment(GetRootComponent());

	DoorMesh = CreateDefaultSubobject <UStaticMeshComponent>("DoorMesh");
	DoorMesh->SetupAttachment(Arrow);

	DoorBorder = CreateDefaultSubobject <UStaticMeshComponent>("DoorBorder");
	DoorBorder->SetupAttachment(GetRootComponent());


}

// Called when the game starts or when spawned
void ADoorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DeltaSecond = DeltaTime;
}

void ADoorBase::InteractPure()
{
	GetWorldTimerManager().SetTimer(InteractDoor, this, &ADoorBase::OpenDoor, 0.01, true);
	
	if (!DoorisOpen)
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), DoorOpenSFX, GetActorLocation());
	}
	
}

void ADoorBase::OpenDoor()
{
	DoorisOpen = true;
	if (!UKismetMathLibrary::EqualEqual_RotatorRotator(Arrow->GetRelativeRotation(), TargetRotation))
	{
		Arrow->SetRelativeRotation(UKismetMathLibrary::RLerp(Arrow->GetRelativeRotation(), TargetRotation, DeltaSecond, false));

	}
	
}

