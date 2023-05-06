// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "KeyList_E.generated.h"

UENUM(BlueprintType)
enum class KeyList : uint8
{
	E_Factory UMETA(DisplayName = "Factory"),
	E_WorkShop UMETA(DisplayName = "WorkShop"),
	E_Lab UMETA(DisplayName = "Lab"),
	E_None UMETA(DisplayName = "None"),


};
UCLASS()
class HORRORPROJECT_API UKeyList_E : public UUserDefinedEnum
{
	GENERATED_BODY()
	
};
