// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SpotLightComponent.h"
#include "Engine/World.h"






// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Camera Setup
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	PlayerCamera->SetupAttachment(GetCapsuleComponent());
	PlayerCamera->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f));
	PlayerCamera->bUsePawnControlRotation = true;
	
	//Phone Setup

	PhoneMesh = CreateDefaultSubobject<UStaticMeshComponent>("Phone");
	PhoneMesh->SetupAttachment(PlayerCamera);

	// SpotLight Setup

	CameraSpotLight = CreateDefaultSubobject<USpotLightComponent>("PhoneLight");
	CameraSpotLight->SetupAttachment(PhoneMesh);
	

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	PlayerController->Possess(this);

	FlashLightState = EFlashLightState::FlashLightOff;
	PhoneMesh->SetRelativeLocation(OffLocation);
	CameraSpotLight->SetHiddenInGame(true);

	CurrentBattery = MaxBattery;
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// AxisMapping

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);

	// ActionMappings
	
}

void APlayerCharacter::MoveForward(float Val)
{
	AddMovementInput(GetActorForwardVector() * Val);
}

void APlayerCharacter::MoveRight(float Val)
{
	AddMovementInput(GetActorRightVector() * Val);
}

void APlayerCharacter::FlashlightSwitch(EFlashLightState NewFlashlightState)
{
	if (b_StartCharge == false)
	{
		switch (NewFlashlightState)
		{



		case FlashLightOn:
			PhoneMesh->SetRelativeLocation(OffLocation);
			CameraSpotLight->SetHiddenInGame(true);
			GetWorldTimerManager().ClearTimer(DrainTimer);

			break;
		case FlashLightOff:
			PhoneMesh->SetRelativeLocation(OnLocation);
			CameraSpotLight->SetHiddenInGame(false);

			GetWorldTimerManager().SetTimer(DrainTimer, this, &APlayerCharacter::DrainBattery, 3.0f, true, 0);

			break;
		default:
			break;


		}
	}
}

void APlayerCharacter::DrainBattery()
{

	UKismetMathLibrary::FClamp(CurrentBattery, 0, MaxBattery);
	CurrentBattery -= DrainAmount;
	

	
}

void APlayerCharacter::ChargeBattery()
{
	PhoneMesh->SetHiddenInGame(true);
	UKismetMathLibrary::FClamp(CurrentBattery, 0, MaxBattery);
	CurrentBattery += ChargeAmount;
}

