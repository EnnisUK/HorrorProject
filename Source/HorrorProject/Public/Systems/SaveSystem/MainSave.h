// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Enums/KeyList_E.h"
#include "MainSave.generated.h"

/**
 * 
 */
UCLASS()
class HORRORPROJECT_API UMainSave : public USaveGame
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditAnywhere)
		FVector PlayerSpawn;


	UPROPERTY(EditAnywhere)
		float CurrentBattery;

	UPROPERTY(EditAnywhere)
		float CurrentSanity;

	UPROPERTY(EditAnywhere)
		bool HasFactoryKey;

	UPROPERTY(EditAnywhere)
		bool b_HasLabKey;

	UPROPERTY(EditAnywhere)
		bool b_HasWorkshopKey;

	UPROPERTY(EditAnywhere)
		bool b_HasFactoryKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<KeyList> KeyListEnum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*> DestroyedActors;

	UPROPERTY(EditAnywhere)
		float MasterVolume;

	UPROPERTY(EditAnywhere)
		float MusicVolume;

	UPROPERTY(EditAnywhere)
		float SFXVolume;

};
