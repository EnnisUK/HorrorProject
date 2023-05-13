// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Characters/HorrorCharacter.h"
#include "Systems/SaveSystem/MainSave.h"
#include "Engine/GameInstance.h"
#include "HorrorGameInstance.generated.h"

/**
 * 
 */
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool isSaving;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool isLoading;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UMainSave* SaveGameInstance;

	AHorrorCharacter* Player;
};
