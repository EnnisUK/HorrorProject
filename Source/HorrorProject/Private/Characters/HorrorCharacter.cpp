// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/HorrorCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SpotLightComponent.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/EngineTypes.h"







// Sets default values
AHorrorCharacter::AHorrorCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Camera Setup
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	PlayerCamera->SetupAttachment(GetCapsuleComponent());
	PlayerCamera->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f));
	PlayerCamera->bUsePawnControlRotation = true;

	//SpringArm Setup

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(PlayerCamera);
	SpringArm->bEnableCameraRotationLag = true;
	
	//Phone Setup

	PhoneMesh = CreateDefaultSubobject<UStaticMeshComponent>("Phone");
	PhoneMesh->SetupAttachment(PlayerCamera);

	// SpotLight Setup

	CameraSpotLight = CreateDefaultSubobject<USpotLightComponent>("PhoneLight");
	CameraSpotLight->SetupAttachment(SpringArm);



}

// Called when the game starts or when spawned
void AHorrorCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	PlayerController->Possess(this);

	FlashLightState = EFlashLightState::FlashLightOff;
	PhoneMesh->SetRelativeLocation(OffLocation);
	CameraSpotLight->SetHiddenInGame(true);

	CurrentBattery = MaxBattery;

	if (PickupWidget)
	{
		PickupWidget->AddToViewport();
	}
	if (HoverWidget)
	{
		HoverWidget->AddToViewport();
	}


	

	
}

// Called every frame
void AHorrorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	HoverTrace();
}

// Called to bind functionality to input
void AHorrorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// AxisMapping
	
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AHorrorCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AHorrorCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);

	// ActionMappings
	
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AHorrorCharacter::InteractInput);
	PlayerInputComponent->BindAction("Flashlight", IE_Pressed, this, &AHorrorCharacter::FlashlightSwitch);
	

}

void AHorrorCharacter::MoveForward(float Val)
{
	AddMovementInput(GetActorForwardVector() * Val);
}

void AHorrorCharacter::MoveRight(float Val)
{
	AddMovementInput(GetActorRightVector() * Val);
}

void AHorrorCharacter::InteractInput()
{
	FVector Loc;
	FRotator Rot;
	FHitResult Hit;
	GetController()->GetPlayerViewPoint(Loc, Rot);
	FVector Start = Loc;
	FVector End = Start + (Rot.Vector() * InteractDistance);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);


	bool DidHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Camera, Params);

	if (DidHit)
	{
		if (Hit.GetActor()->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
		{
			Cast<IInteractInterface>(Hit.GetActor())->InteractPure();
		}
	}
	DrawDebugLine(GetWorld(), Start, End, FColor::Orange, true);
}

void AHorrorCharacter::HoverTrace()
{
	FVector Loc;
	FRotator Rot;
	FHitResult Hit;
	GetController()->GetPlayerViewPoint(Loc, Rot);
	FVector Start = Loc;
	FVector End = Start + (Rot.Vector() * InteractDistance);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool DidHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Camera, Params);

	if (DidHit)
	{
		if (Hit.GetActor()->ActorHasTag("display"))
		{
			Crosshair->SetBrushFromTexture(InteractCrosshair);

		}
		
	}
	else
	{
		Crosshair->SetBrushFromTexture(DefaultCrosshair);
	}
}

void AHorrorCharacter::ClearMessage()
{
	HasMessage = false;
	PhoneWidget->PlayAnimation(PulseIn, 0, 1, EUMGSequencePlayMode::Reverse);
	hasShownMessage = false;

}

void AHorrorCharacter::HidePhoneWidget()
{
	PhoneWidget->RemoveFromParent();
}

void AHorrorCharacter::ShowPhoneWidget()
{
	PhoneWidget->AddToViewport();
}

void AHorrorCharacter::HidePhoneFunction()
{
	if (HidePhone)
	{
		PhoneMesh->SetHiddenInGame(true, true);
		CameraSpotLight->SetHiddenInGame(true);
	}
	else
	{
		PhoneMesh->SetHiddenInGame(false, true);
	}
}

void AHorrorCharacter::PickupHud()
{

	PickupWidget->PlayAnimation(FadeInDisplay);


}



void AHorrorCharacter::DrainSanity(float SanityDrainAmount)
{
	if (!IsInSanityRoom)
	{
		CurrentSanity -= SanityDrainAmount;
		CurrentSanity = UKismetMathLibrary::FClamp(CurrentSanity, 0, MaxSanity);

		if (CurrentSanity == 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("Dead"));
		}

	}

}


FString AHorrorCharacter::Message(FString TextMessage)
{

	return TextMessage;
}





void AHorrorCharacter::InteractPure()
{
}

void AHorrorCharacter::SetDisplayName()
{
}

void AHorrorCharacter::FlashlightSwitch()
{
	if (b_StartCharge == false && CurrentBattery > 0.f)
	{
		switch (FlashLightState)
		{



		case FlashLightOn:
			PhoneMesh->SetRelativeLocation(OffLocation);
			CameraSpotLight->SetHiddenInGame(true);
			GetWorldTimerManager().ClearTimer(DrainTimer);
			FlashLightState = EFlashLightState::FlashLightOff;
			HidePhoneWidget();
			if (PhoneCloseSFX)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), PhoneCloseSFX);

			}
			break;
		case FlashLightOff:

			if (HasMessage && hasShownMessage == false)
			{
				PhoneWidget->PlayAnimation(PulseIn);
				hasShownMessage = true;
				DrainSanity(10);
				GetWorldTimerManager().SetTimer(MessageTimer, this, &AHorrorCharacter::ClearMessage, 5, false);
			}
			PhoneMesh->SetRelativeLocation(OnLocation);
			CameraSpotLight->SetHiddenInGame(false);
			FlashLightState = EFlashLightState::FlashLightOn;
			GetWorldTimerManager().SetTimer(DrainTimer, this, &AHorrorCharacter::DrainBattery, 3.0f, true, 3.0f);
			ShowPhoneWidget();
			if (PhoneOpenSFX)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), PhoneOpenSFX);
			}
			
			break;
		default:
			break;


		}
	}
}

void AHorrorCharacter::DrainBattery()
{

	
	CurrentBattery -= DrainAmount;
	CurrentBattery = UKismetMathLibrary::FClamp(CurrentBattery, 0, MaxBattery);


	if (CurrentBattery == 0)
	{
		if (PhoneOff) 
		{
			PhoneMesh->SetMaterial(2, PhoneOff);
			CameraSpotLight->SetHiddenInGame(true);
			PhoneWidget->RemoveFromParent();
		}
	}

	
}

void AHorrorCharacter::ChargeBattery()
{
	CurrentBattery += ChargeAmount;
	CurrentBattery = UKismetMathLibrary::FClamp(CurrentBattery, 0, MaxBattery);
}

