// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/Key/KeyPickup.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AKeyPickup::AKeyPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>("KeyMesh");



}

// Called when the game starts or when spawned
void AKeyPickup::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AHorrorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	switch (KeyID)
	{
	case KeyList::E_Factory:
		KeyMesh->SetMaterial(0, FactoryMat);
		break;
	case KeyList::E_WorkShop:
		KeyMesh->SetMaterial(0, WorkshopMat);
		break;
	case KeyList::E_Lab:
		KeyMesh->SetMaterial(0, LabMat);
		break;
	default:
		break;
	}

	
}

// Called every frame
void AKeyPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKeyPickup::InteractPure()
{
	if (Player)
	{
		Player->KeyListEnum.AddUnique(KeyID);
		Destroy();
	}
}

