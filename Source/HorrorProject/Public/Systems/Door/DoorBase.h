// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Systems/Interfaces/InteractInterface.h"
#include "DoorBase.generated.h"

class UArrowComponent;
class UStaticMeshComponent;
class USoundBase;

UCLASS()
class HORRORPROJECT_API ADoorBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorBase();

	// Properties


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UArrowComponent* Arrow;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* DoorOpenSFX;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* DefaultSceneRoot;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* DoorBorder;

	UPROPERTY(EditAnywhere)
		FRotator TargetRotation;

	bool DoorisOpen;

	float DeltaSecond;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	virtual void InteractPure() override;

	void OpenDoor();

	FTimerHandle InteractDoor;
};
