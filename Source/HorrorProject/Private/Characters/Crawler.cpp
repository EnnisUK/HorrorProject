// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Crawler.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ACrawler::ACrawler()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACrawler::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AHorrorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

}

// Called every frame
void ACrawler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AttackPlayer();
}

// Called to bind functionality to input
void ACrawler::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACrawler::AttackPlayer()
{
	if (GetDistanceTo(Player) < AttackDistance && !IsAttacking)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("Attack"));
	}
}

