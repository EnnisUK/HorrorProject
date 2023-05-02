// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HorrorCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Crawler.generated.h"

UCLASS()
class HORRORPROJECT_API ACrawler : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACrawler();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void AttackPlayer();

	AHorrorCharacter* Player;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float AttackDistance;

	bool IsAttacking;

};
