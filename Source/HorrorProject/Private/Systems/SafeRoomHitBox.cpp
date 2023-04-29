// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/SafeRoomHitBox.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASafeRoomHitBox::ASafeRoomHitBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitBox = CreateDefaultSubobject<UBoxComponent>("HitBox");
	RootComponent = HitBox;

}

// Called when the game starts or when spawned
void ASafeRoomHitBox::BeginPlay()
{
	Super::BeginPlay();

	HitBox->OnComponentBeginOverlap.AddDynamic(this, &ASafeRoomHitBox::BoxOverlap);

	HitBox->OnComponentEndOverlap.AddDynamic(this, &ASafeRoomHitBox::BoxEndOverlap);

	Player = Cast<AHorrorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
}

// Called every frame
void ASafeRoomHitBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASafeRoomHitBox::BoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Player)
	{
		Player->IsInSanityRoom = true;
	}
	
}

void ASafeRoomHitBox::BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == Player)
	{
		Player->IsInSanityRoom = false;

	}
	
}

