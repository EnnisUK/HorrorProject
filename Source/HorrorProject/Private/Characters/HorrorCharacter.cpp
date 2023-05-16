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
#include "Kismet/KismetStringLibrary.h"
#include "Components/PointLightComponent.h"
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
	
	//Create Lighter

	Lighter = CreateDefaultSubobject<UStaticMeshComponent>("Lighter");
	Lighter->SetupAttachment(PlayerCamera);

	// Create Point light

	LighterLight = CreateDefaultSubobject<UPointLightComponent>("LighterLight");
	LighterLight->SetupAttachment(Lighter);


}

// Called when the game starts or when spawned
void AHorrorCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	GameInstance = Cast<UHorrorGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	GameInstance->LoadGame();


	

	if (PickupWidget)
	{
		PickupWidget->AddToViewport();
	}
	if (HoverWidget)
	{
		HoverWidget->AddToViewport();
		if (!b_IsInGameLevel)
		{
			HoverWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}


	

	
}

// Called every frame
void AHorrorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (APawn::IsPawnControlled())
	{
		HoverTrace();
	}

	if (GetVelocity() == FVector(0,0,0))
	{
		b_IsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = 400;
		APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

		CameraManager->StopCameraShake(CameraShakeInstance);
	}
	
}

// Called to bind functionality to input
void AHorrorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// AxisMapping
	
	PlayerInputComponent->BindAxis("Move Forward", this, &AHorrorCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Backwards", this, &AHorrorCharacter::MoveBackwards);
	PlayerInputComponent->BindAxis("Move Right", this, &AHorrorCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Move Left", this, &AHorrorCharacter::MoveLeft);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);

	// ActionMappings
	
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AHorrorCharacter::InteractInput);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AHorrorCharacter::SprintFunction);
	

}

void AHorrorCharacter::MoveForward(float Val)
{

	AddMovementInput(GetActorForwardVector() * Val);
}

void AHorrorCharacter::MoveBackwards(float Val)
{
	AddMovementInput(GetActorForwardVector() * Val);
}
	

void AHorrorCharacter::MoveRight(float Val)
{
	AddMovementInput(GetActorRightVector() * Val);

}

void AHorrorCharacter::MoveLeft(float Val)
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









void AHorrorCharacter::PickupHud()
{

	PickupWidget->PlayAnimation(FadeInDisplay);


}

void AHorrorCharacter::DisableMovement()
{
	GetCharacterMovement()->DisableMovement();
}

void AHorrorCharacter::EnableMovement()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void AHorrorCharacter::PlayFootSteps()
{
	FVector SoundLocation = GetActorLocation() - FVector(0, 0, 44);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FootStepSound, SoundLocation);

}

void AHorrorCharacter::SprintFunction()
{
	if (!b_IsSprinting)
	{
		b_IsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = 550;
		APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

		CameraShakeInstance = CameraManager->StartCameraShake(CamShakeBase);
	}
	else
	{
		b_IsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = 400;
		APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

		CameraManager->StopCameraShake(CameraShakeInstance);
	}
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




void AHorrorCharacter::InteractPure()
{
}

void AHorrorCharacter::SetDisplayName()
{
}


