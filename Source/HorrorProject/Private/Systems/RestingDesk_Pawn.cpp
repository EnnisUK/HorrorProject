// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/RestingDesk_Pawn.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Systems/GI/HorrorGameInstance.h"
#include "Kismet/KismetMathLibrary.h"



// Sets default values
ARestingDesk_Pawn::ARestingDesk_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create Desk Component
	Desk = CreateDefaultSubobject<UStaticMeshComponent>("DeskMesh");

	// Create Typewriter

	Typewriter = CreateDefaultSubobject<UStaticMeshComponent>("Typewriter");
	Typewriter->SetupAttachment(Desk);

	// Create Chair Component
	Chair = CreateDefaultSubobject<UStaticMeshComponent>("ChairMesh");
	Chair->SetupAttachment(Desk);

	// Create Camera Component
	DeskCamera = CreateDefaultSubobject<UCameraComponent>("DeskCamera");
	DeskCamera->SetupAttachment(Desk);


}

// Called when the game starts or when spawned
void ARestingDesk_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Player = Cast<AHorrorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));


	
}

// Called every frame
void ARestingDesk_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (b_IsResting)
	{
		if (Player->CurrentSanity < 100)
		{
			Player->CurrentSanity += 5 * DeltaTime;
		}
		
	}

}

// Called to bind functionality to input
void ARestingDesk_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARestingDesk_Pawn::SetDisplayName()
{
}

void ARestingDesk_Pawn::SetPlayerLocation()
{
	Player->SetActorLocation(NewActorLocation);
	FRotator ActorRotation = UKismetMathLibrary::FindLookAtRotation(Player->GetActorLocation(), GetActorLocation());
	Player->SetActorRotation(ActorRotation);
}

void ARestingDesk_Pawn::InteractPure()
{
	if (PlayerController)
	{
		if (!b_IsResting)
		{
			UHorrorGameInstance* GameInstance = Cast<UHorrorGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			GameInstance->PlayerSpawn = NewActorLocation;
			Player->HoverWidget->SetVisibility(ESlateVisibility::Hidden);
			PlayerController->SetViewTargetWithBlend(this, 1.0f, EViewTargetBlendFunction::VTBlend_Cubic, 1.0f);
			b_IsResting = true;
			PlayerController->SetShowMouseCursor(true);
			PlayerController->bEnableMouseOverEvents = true;
			PlayerController->bEnableClickEvents = true;
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController);
			GetWorldTimerManager().SetTimer(CameraWaitTime, this, &ARestingDesk_Pawn::SetPlayerLocation, 1.1, false);
		}
		else
		{
			UHorrorGameInstance* GameInstance = Cast<UHorrorGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			Player->HoverWidget->SetVisibility(ESlateVisibility::Visible);
			PlayerController->SetViewTargetWithBlend(Player, 1.0f, EViewTargetBlendFunction::VTBlend_Cubic, 1.0f);
			b_IsResting = false;
			PlayerController->SetShowMouseCursor(false);
			PlayerController->bEnableMouseOverEvents = false;
			PlayerController->bEnableClickEvents = false;
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
			GameInstance->SaveGame();
			
			
		}

	}
}

