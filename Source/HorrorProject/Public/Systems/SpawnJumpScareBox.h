// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Characters/HorrorCharacter.h"
#include "SpawnJumpScareBox.generated.h"

class UBoxComponent;

UCLASS()
class HORRORPROJECT_API ASpawnJumpScareBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnJumpScareBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* HitBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enum", meta = (ExposeOnSpawn = "true"))
		TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enum", meta = (ExposeOnSpawn = "true"))
		 FVector SpawnLocation;


	UFUNCTION()
		void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void ActivateJumpScare();

	AHorrorCharacter* Player;

};
