// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Characters/HorrorCharacter.h"
#include "Interfaces/InteractInterface.h"
#include "ChargingStation.generated.h"


UENUM(BlueprintType)
enum EChargingState
{
	Charging,
	NotCharging
};


class UStaticMeshComponent;

UCLASS()
class HORRORPROJECT_API AChargingStation : public AActor, public IInteractInterface
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMeshComponent* Mesh;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMeshComponent* PhoneMesh;

	FTimerHandle ChargeTimer;

	AHorrorCharacter* HorrorCharacter;

	// Enums

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TEnumAsByte<EChargingState> ChargingState;



	virtual void InteractPure() override;
	
	virtual void SetDisplayName() override; // C++ Function

	void CallCharging();

	UFUNCTION(BlueprintCallable)
		void ChargerClicked();

};
