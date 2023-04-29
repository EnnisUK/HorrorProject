// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Systems/Interfaces/InteractInterface.h"
#include "Animation/WidgetAnimation.h"
#include "HorrorCharacter.generated.h"



class UCameraComponent;
class USpotLightComponent;
class USoundBase;
class USpringArmComponent;

UENUM(BlueprintType)
enum EFlashLightState
{
	FlashLightOn,
	FlashLightOff,
};

UCLASS()
class HORRORPROJECT_API AHorrorCharacter : public ACharacter, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHorrorCharacter();

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


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm;

	APlayerController* PlayerController;


	// Character Inputs

	void MoveForward(float Val);

	void MoveRight(float Val);

	void InteractInput();

	void ClearMessage();

	void HidePhoneWidget();

	void ShowPhoneWidget();

	UFUNCTION(BlueprintCallable)
	void DrainSanity(float SanityDrainAmount);

	UFUNCTION(BlueprintCallable)
	FString Message(FString TextMessage);

	// Character Variables

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float InteractDistance = 200.f;



		virtual void InteractPure() override;

		UPROPERTY(BlueprintReadOnly)
		bool IsInSanityRoom;


		UPROPERTY(BlueprintReadOnly)
			bool HidePhone;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			UUserWidget* PhoneWidget;


		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
			USoundBase* PhoneOpenSFX;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
			USoundBase* PhoneCloseSFX;


		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
			USoundBase* PhoneMessageSFX;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
			bool HasMessage;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
			float CurrentSanity;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
			float MaxSanity = 100.f;

		bool hasShownMessage = false;


		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
			UWidgetAnimation* PulseIn;

		FTimerHandle MessageTimer;

		FTimerHandle DrainSanityTimer;
			

	UFUNCTION(BlueprintCallable)
	void FlashlightSwitch();

	// Flashlight Variables

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpotLightComponent* CameraSpotLight;

	FTimerHandle DrainTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
	FVector OffLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flashlight")
	FVector OnLocation;

	FTimerHandle FlashlightTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EFlashLightState> FlashLightState;

	UPROPERTY(EditDefaultsOnly)
		float DrainAmount;

	UPROPERTY(EditDefaultsOnly)
		float ChargeAmount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxBattery = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentBattery;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterial* PhoneOff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterial* PhoneOn;


	// Flashlight Functions

	void DrainBattery();

	void ChargeBattery();

	UPROPERTY(BlueprintReadOnly)
	bool b_StartCharge = false;

};
