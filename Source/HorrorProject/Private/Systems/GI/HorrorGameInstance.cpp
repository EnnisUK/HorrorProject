// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/GI/HorrorGameInstance.h"
#include "Characters/HorrorCharacter.h"
#include "Kismet/GameplayStatics.h"




void UHorrorGameInstance::Init()
{
	UGameInstance::Init();

	
	

}

void UHorrorGameInstance::SaveGame()
{
	if (UGameplayStatics::DoesSaveGameExist("MainSave", 0))
	{
		if (Player)
		{
			SaveGameInstance->PlayerSpawn = Player->GetActorLocation();
			SaveGameInstance->CurrentSanity = Player->CurrentSanity;
			SaveGameInstance->b_HasFactoryKey = Player->FactoryKey;
			SaveGameInstance->b_HasLabKey = Player->LabKey;
			SaveGameInstance->b_HasWorkshopKey = Player->WorkshopKey;
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("Player VariablesSaved"));
		}
		
		SaveGameInstance->MasterVolume = MasterVolume;
		SaveGameInstance->MusicVolume = MusicVolume;
		SaveGameInstance->SFXVolume = SFXVolume;
		SaveGameInstance->MouseSens = MouseSens;

		isSaving = true;

		// Save the game instance
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, "MainSave", 0);

		
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("NotSaved"));
	}

		

}

void UHorrorGameInstance::LoadGame()
{
	if (UGameplayStatics::DoesSaveGameExist("MainSave", 0))
	{
		SaveGameInstance = Cast<UMainSave>(UGameplayStatics::CreateSaveGameObject(UMainSave::StaticClass()));

		Player = Cast<AHorrorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		SaveGameInstance = Cast<UMainSave>(UGameplayStatics::LoadGameFromSlot("MainSave", 0));
		if (Player)
		{
			PlayerSpawn = SaveGameInstance->PlayerSpawn;
			Player->SetActorLocation(PlayerSpawn);
			Player->CurrentSanity = SaveGameInstance->CurrentSanity;
			Player->FactoryKey = SaveGameInstance->b_HasFactoryKey;
			Player->WorkshopKey = SaveGameInstance->b_HasWorkshopKey;
			Player->LabKey = SaveGameInstance->b_HasLabKey;
			GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("Player Variables loaded"));
		}

		MasterVolume = SaveGameInstance->MasterVolume;
		SFXVolume = SaveGameInstance->SFXVolume;
		MusicVolume = SaveGameInstance->MusicVolume;
		MouseSens = SaveGameInstance->MouseSens;

		isLoading = true;
	}
	else
	{
		SaveGameInstance = Cast<UMainSave>(UGameplayStatics::CreateSaveGameObject(UMainSave::StaticClass()));

		UGameplayStatics::SaveGameToSlot(SaveGameInstance, "MainSave", 0);

		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("CreatedSave"));
	}
	



}
