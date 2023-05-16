// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Systems/Interfaces/InteractInterface.h"
#include "Animation/WidgetAnimation.h"
#include "Enums/KeyList_E.h"
#include "Components/Image.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Systems/GI/HorrorGameInstance.h"
#include "HorrorCharacter.generated.h"



class UCameraComponent;
class USpotLightComponent;
class USoundBase;
class USpringArmComponent;
class UPointLightComponent;

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



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* PlayerCamera;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm;

	APlayerController* PlayerController;

	//Casts

	UHorrorGameInstance* GameInstance;

	// Character Inputs

	void MoveForward(float Val);

	void MoveBackwards(float Val);

	void MoveRight(float Val);

	void MoveLeft(float Val);

	void InteractInput();

	void HoverTrace();


	void PickupHud();

	void DisableMovement();

	void EnableMovement();

	void PlayFootSteps();

	void SprintFunction();

	UFUNCTION(BlueprintCallable)
	void DrainSanity(float SanityDrainAmount);


	// Character Variables

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UCameraShakeBase> CamShakeBase;

	UCameraShakeBase* CameraShakeInstance;

	bool b_IsSprinting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Lighter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPointLightComponent* LighterLight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float InteractDistance = 200.f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool b_IsInGameLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float DetectionDistance = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enum", meta = (ExposeOnSpawn = "true"))
		TArray<KeyList> KeyListEnum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* DefaultCrosshair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* InteractCrosshair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UImage* Crosshair;



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector StartLocation;
	
		// Interaction Void
		virtual void InteractPure() override;

		virtual void SetDisplayName() override;

		UPROPERTY(BlueprintReadOnly)
		bool IsInSanityRoom;



		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			UUserWidget* HoverWidget;


		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			UUserWidget* PickupWidget;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			FString CollectedDisplayName;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			UWidgetAnimation* FadeInDisplay;

		UPROPERTY(BlueprintReadWrite)
		bool HoverWidgetOnScreen;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
			bool HasMessage;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
			float CurrentSanity;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
			float MaxSanity = 100.f;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			bool SeenEnemy;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			bool FactoryKey;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			bool WorkshopKey;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			bool LabKey;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			FString HoverName;

		bool hasShownMessage = false;


		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
			UWidgetAnimation* PulseIn;

		FTimerHandle MessageTimer;

		FTimerHandle DrainSanityTimer;

		FTimerHandle DetectionCall;

		FTimerHandle FootStepTimer;

		UPROPERTY(EditAnywhere, Category = "SFX")
			USoundBase* FootStepSound;

		bool StepSoundIsPlaying;
			

};
