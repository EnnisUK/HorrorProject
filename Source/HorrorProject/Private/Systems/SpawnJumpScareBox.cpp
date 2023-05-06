// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/SpawnJumpScareBox.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"





// Sets default values
ASpawnJumpScareBox::ASpawnJumpScareBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitBox = CreateDefaultSubobject<UBoxComponent>("HitBox");

}

// Called when the game starts or when spawned
void ASpawnJumpScareBox::BeginPlay()
{
	Super::BeginPlay();
	
	HitBox->OnComponentBeginOverlap.AddDynamic(this, &ASpawnJumpScareBox::OnBoxOverlap);

}

// Called every frame
void ASpawnJumpScareBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	Player = Cast<AHorrorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void ASpawnJumpScareBox::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Player)
	{
		ActivateJumpScare();
		Destroy();
	}
	
}

void ASpawnJumpScareBox::ActivateJumpScare()
{
	FActorSpawnParameters SpawnParams;

	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;


	

	GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, GetActorRotation(), SpawnParams);

}

