// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractInterface.h"
#include "RestingDesk.generated.h"

class UStaticMeshComponent;
class UCameraComponent;

UCLASS()
class HORRORPROJECT_API ARestingDesk : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARestingDesk();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Actor Components

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Desk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Chair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* DeskCamera;

	// Interfaces

	virtual void InteractPure() override;

	virtual void SetDisplayName() override;

	// Actor Variables

	bool b_IsResting;


};
