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
	
	HorrorCharacter = Cast<AHorrorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (HorrorCharacter != NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("Cast Successfull"));
	}

	ChargingState = EChargingState::NotCharging;
}

// Called every frame
void AChargingStation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

void AChargingStation::InteractPure()
{

	switch (ChargingState)
	{
	case Charging:
		GetWorldTimerManager().ClearTimer(ChargeTimer);
		PhoneMesh->SetHiddenInGame(true);
		HorrorCharacter->b_StartCharge = false;
		ChargingState = EChargingState::NotCharging;
		HorrorCharacter->PhoneMesh->SetHiddenInGame(false);
		HorrorCharacter->PhoneMesh->SetRelativeLocation(HorrorCharacter->OffLocation);
		HorrorCharacter->HidePhone = false;
		break;
	case NotCharging:
		PhoneMesh->SetHiddenInGame(false);
		HorrorCharacter->b_StartCharge = true;
		ChargingState = EChargingState::Charging;
		HorrorCharacter->FlashLightState = EFlashLightState::FlashLightOff;
		HorrorCharacter->PhoneMesh->SetHiddenInGame(true, true);
		HorrorCharacter->HidePhoneWidget();
		HorrorCharacter->HidePhone = true;
		GetWorldTimerManager().SetTimer(ChargeTimer, this, &AChargingStation::CallCharging, 2.0f, true);
		GetWorldTimerManager().ClearTimer(HorrorCharacter->DrainTimer);


		break;
	default:
		GetWorldTimerManager().ClearTimer(ChargeTimer);
		PhoneMesh->SetHiddenInGame(true);
		HorrorCharacter->b_StartCharge = false;
		ChargingState = EChargingState::NotCharging;
		break;
	}
	

	
}

void AChargingStation::CallCharging()
{
	HorrorCharacter->ChargeBattery();
}

