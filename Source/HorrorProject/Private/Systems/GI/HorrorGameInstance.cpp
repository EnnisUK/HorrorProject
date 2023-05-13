// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/GI/HorrorGameInstance.h"
#include "Kismet/GameplayStatics.h"




void UHorrorGameInstance::Init()
{
	UGameInstance::Init();

	Player = Cast<AHorrorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

}

void UHorrorGameInstance::SaveGame()
{
	if (UGameplayStatics::DoesSaveGameExist("MainSave", 0))
	{
		SaveGameInstance->CurrentBattery = Player->CurrentBattery;
		SaveGameInstance->CurrentSanity = Player->CurrentSanity;
		SaveGameInstance->b_HasFactoryKey = Player->FactoryKey;
		SaveGameInstance->b_HasLabKey = Player->LabKey;
		SaveGameInstance->b_HasWorkshopKey = Player->WorkshopKey;
		SaveGameInstance->MasterVolume = MasterVolume;
		SaveGameInstance->MusicVolume = MusicVolume;
		SaveGameInstance->SFXVolume = SFXVolume;

		isSaving = true;

		// Save the game instance
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, "MainSave", 0);
	}
	else
	{
		// Create Save Game if it does not exist
		SaveGameInstance = Cast<UMainSave> (UGameplayStatics::CreateSaveGameObject(UMainSave::StaticClass()));
	}
}

void UHorrorGameInstance::LoadGame()
{
	if (UGameplayStatics::DoesSaveGameExist("MainSave", 0))
	{
		SaveGameInstance = Cast<UMainSave>(UGameplayStatics::LoadGameFromSlot("MainSave", 0));

		Player->CurrentBattery = SaveGameInstance->CurrentBattery;
		Player->CurrentSanity = SaveGameInstance->CurrentSanity;
		Player->FactoryKey = SaveGameInstance->b_HasFactoryKey;
		Player->WorkshopKey = SaveGameInstance->b_HasWorkshopKey;
		Player->LabKey = SaveGameInstance->b_HasLabKey;
		MasterVolume = SaveGameInstance->MasterVolume;
		SFXVolume = SaveGameInstance->SFXVolume;
		MusicVolume = SaveGameInstance->MusicVolume;

		isLoading = true;


	}

}
