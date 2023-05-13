// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Systems/SaveSystem/MainSave.h"
#include "Engine/GameInstance.h"
#include "HorrorGameInstance.generated.h"

/**
 * 
 */

class AHorrorCharacter;
UCLASS()
class HORRORPROJECT_API UHorrorGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	virtual void Init();


public:

	UFUNCTION(BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintCallable)
	void LoadGame();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MasterVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SFXVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MusicVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AActor*> DestroyedActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isSaving;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isLoading;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UMainSave* SaveGameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		AHorrorCharacter* Player;
};
