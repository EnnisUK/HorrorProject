// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/InteractInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/HorrorCharacter.h"
#include "Systems/ChargingStation.h"
#include "RestingDesk_Pawn.generated.h"

class UStaticMeshComponent;
class UCameraComponent;

UCLASS()
class HORRORPROJECT_API ARestingDesk_Pawn : public APawn, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARestingDesk_Pawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Actor Components

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Desk;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Typewriter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Chair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* DeskCamera;

	// Interfaces

	virtual void InteractPure() override;

	virtual void SetDisplayName() override;

	// Functions

	void SetPlayerLocation();

	// Actor Variables

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool b_IsResting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector NewActorLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AChargingStation* ChargeStationRef;

	APlayerController* PlayerController;

	AHorrorCharacter* Player;

	FTimerHandle CameraWaitTime;

};
