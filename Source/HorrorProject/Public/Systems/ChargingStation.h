// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Characters/PlayerCharacter.h"
#include "ChargingStation.generated.h"


class UStaticMeshComponent;

UCLASS()
class HORRORPROJECT_API AChargingStation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChargingStation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* Mesh;


	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* PhoneMesh;

	APlayerCharacter* Player;

	FTimerHandle ChargeTimer;

};
