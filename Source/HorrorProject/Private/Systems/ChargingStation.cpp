// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/ChargingStation.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"



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


	ChargingState = EChargingState::NotCharging;
}

// Called every frame
void AChargingStation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

void AChargingStation::InteractPure()
{

	

	
}

void AChargingStation::SetDisplayName()
{

	switch (ChargingState)
	{
	case Charging:

		HorrorCharacter->HoverName = "E To Pickup";
		
		break;
	case NotCharging:

		HorrorCharacter->HoverName = "E To Charge Phone";
		
		break;
	default:
		break;
	}
}

void AChargingStation::CallCharging()
{
	HorrorCharacter->ChargeBattery();
}

void AChargingStation::ChargerClicked()
{
	switch (ChargingState)
	{
	case Charging:
		GetWorldTimerManager().ClearTimer(ChargeTimer);
		PhoneMesh->SetHiddenInGame(true);
		HorrorCharacter->HoverWidgetOnScreen = false;
		HorrorCharacter->b_StartCharge = false;
		ChargingState = EChargingState::NotCharging;
		HorrorCharacter->PhoneMesh->SetHiddenInGame(false);
		HorrorCharacter->PhoneMesh->SetRelativeLocation(HorrorCharacter->OffLocation);
		HorrorCharacter->HidePhone = false;
		HorrorCharacter->HidePhoneFunction();
		if (HorrorCharacter->CurrentBattery > 0)
		{
			HorrorCharacter->PhoneMesh->SetMaterial(2, HorrorCharacter->PhoneOn);
		}
		break;
	case NotCharging:
		PhoneMesh->SetHiddenInGame(false);
		HorrorCharacter->b_StartCharge = true;
		ChargingState = EChargingState::Charging;
		HorrorCharacter->HoverWidgetOnScreen = false;
		HorrorCharacter->FlashLightState = EFlashLightState::FlashLightOff;
		HorrorCharacter->HidePhoneWidget();
		HorrorCharacter->HidePhone = true;
		HorrorCharacter->HidePhoneFunction();
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

