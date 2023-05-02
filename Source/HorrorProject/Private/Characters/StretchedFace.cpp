// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/StretchedFace.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Characters/HorrorCharacter.h"

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
	
	Player = Cast<AHorrorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void AStretchedFace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator LookatTarget = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Player->GetActorLocation());

	SetActorRotation(LookatTarget);

	LineTrace();
}

// Called to bind functionality to input
void AStretchedFace::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AStretchedFace::LineTrace()
{
	FVector Start = GetMesh()->GetSocketLocation("LineTraceHead");
	FVector End = Player->GetActorLocation();

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	const bool bDidSee = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Camera, Params);

	if (bDidSee)
	{
		if (HitResult.GetActor() == Player) 
		{
			if (GetDistanceTo(Player) < SightDistance)
			{
				Player->SeenEnemy = true;
			}
			else
			{
				Player->SeenEnemy = false;
			}
		}
		else
		{
			Player->SeenEnemy = false;
		}
		
	}

}


