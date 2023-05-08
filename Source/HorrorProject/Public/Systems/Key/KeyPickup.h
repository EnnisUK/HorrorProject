// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enums/KeyList_E.h"
#include "Systems/Interfaces/InteractInterface.h"
#include "Characters/HorrorCharacter.h"
#include "Materials/MaterialInterface.h"
#include "KeyPickup.generated.h"

class UStaticMeshComponent;

UCLASS()
class HORRORPROJECT_API AKeyPickup : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeyPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InteractPure() override;

	virtual void SetDisplayName() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enum", meta = (ExposeOnSpawn = "true"))
		KeyList KeyID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* KeyMesh;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* FactoryMat;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* LabMat;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* WorkshopMat;

	AHorrorCharacter* Player;


};
