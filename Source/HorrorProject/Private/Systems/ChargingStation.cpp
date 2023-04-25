// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/ChargingStation.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AChargingStation::AChargingStation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("ChargerMesh");
	RootComponent = Mesh;

	PhoneMesh = CreateDefaultSubobject<UStaticMeshComponent>("PhoneMesh");
	PhoneMesh->SetupAttachment(GetRootComponent());
	PhoneMesh->SetHiddenInGame(true);

}

// Called when the game starts or when spawned
void AChargingStation::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
}

// Called every frame
void AChargingStation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Player != NULL)
	{
		if (Player->b_StartCharge)
		{
			Player->ChargeBattery();
			PhoneMesh->SetHiddenInGame(false);
		}
	}
	

}

void AChargingStation::InteractPure()
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, TEXT("PureCalled"));
}

