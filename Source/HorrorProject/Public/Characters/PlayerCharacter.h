// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"


class UCameraComponent;
class USpotLightComponent;

UENUM(BlueprintType)
enum EFlashLightState
{
	FlashLightOn,
	FlashLightOff,
};

UCLASS()
class HORRORPROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Character Components

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* PhoneMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* PlayerCamera;

	APlayerController* PlayerController;


	// Character Inputs

	void MoveForward(float Val);

	void MoveRight(float Val);

	UFUNCTION(BlueprintCallable)
	void FlashlightSwitch(EFlashLightState NewFlashlightState);

	// Flashlight Variables

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpotLightComponent* CameraSpotLight;

	FTimerHandle DrainTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
	FVector OffLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
	FVector OnLocation;

	FTimerHandle FlashlightTimer;

	
	EFlashLightState FlashLightState;

	UPROPERTY(EditDefaultsOnly)
		float DrainAmount;

	UPROPERTY(EditDefaultsOnly)
		float ChargeAmount;

	float MaxBattery = 100.f;
	float CurrentBattery;

	// Flashlight Functions

	void DrainBattery();

	void ChargeBattery();

	bool b_StartCharge = false;

};
