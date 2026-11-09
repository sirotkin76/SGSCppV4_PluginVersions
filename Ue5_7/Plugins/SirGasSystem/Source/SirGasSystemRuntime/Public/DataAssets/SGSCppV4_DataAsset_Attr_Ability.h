// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameplayTagContainer.h"
#include "DataAssets/SGSCppV4_DataAsset_Attr.h"
#include "SGSCppV4_DataAsset_Attr_Ability.generated.h"

class UUserWidget;
class UGameplayEffect;
class UGameplayAbility;
/**
 * 
*/


UCLASS()
class SIRGASSYSTEMRUNTIME_API USGSCppV4_DataAsset_Attr_Ability : public USGSCppV4_DataAsset_Attr
{
	GENERATED_BODY()
	
public:

	USGSCppV4_DataAsset_Attr_Ability();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ParentForUpdateLevel")
	TSoftObjectPtr <UPrimaryDataAsset> Parent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayAbilityForActivate")
	TSubclassOf <UGameplayAbility> GameplayAbility;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffectsForUpdate")
	TArray<TSubclassOf<UGameplayEffect>> UpdateGameplayEffectByClass;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityTag")
	FGameplayTagContainer AbilityTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilityTag")
	FGameplayTag CooldownTag;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	UTexture2D* Icon;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FString IconName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FString NameShort;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FString NameFull;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FString DescriptionShort;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FString DescriptionFull;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FString TypeAbility;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FString TypeDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 1, Min = 1))
	int32 MaxLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 1, Min = 1))
	TArray<FString> ArrStringForInfo;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	float CoolDownDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	float Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	UMaterialInterface* UI_Material;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	TSubclassOf<UUserWidget> UI_WidgetIconForAbility;


};
