// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "SGSCppV4_DataAsset_Attr.h"
#include "SGSCppV4_DataAsset_Attr_InventorySlot.generated.h"

class UGameplayAbility;
class SGSCppV4_DataAsset_Attr_Recipe;
class UGameplayEffect;

/**
 * 
 */


UCLASS(Blueprintable, Category = "SGSCpp|BFL")
class SIRGASSYSTEMRUNTIME_API USGSCppV4_DataAsset_Attr_InventorySlot : public USGSCppV4_DataAsset_Attr
{
	GENERATED_BODY()
	
public:
	
	USGSCppV4_DataAsset_Attr_InventorySlot();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	bool AutoEquip;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	bool Stackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 1, Min = 1))
	int32 CountMax = 1;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float Cost;

	// *************
	// Данный аттрибут должен быть массивом, так как, один компонент может находится в 2 или более типах.
	// Пример - вода, вода может быть типом - крафт и типом - пища и типом - вода.
	
	// This attribute must be an array, since a single component can belong to two or more types.
	// For example, water can be classified as a crafting item, a food item, and a water item.
	
	/*ArrName.Add(TEXT("InventoryType"), "");*/
	
	// *************
	// Чтобы не запутаться данный параметр вывел в одной области с основным типом.
	// To avoid confusion, I’ve placed this parameter in the same area as the main type.
	/*ArrName.Add(TEXT("InventorySubType"), "");*/
	// *************
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	TArray<FName> InventorySlotTypes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	TArray<FName> InventorySlotSubType;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TSoftObjectPtr <UPrimaryDataAsset> RecipeForPlayerHave;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TSubclassOf<AActor> PickUpActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Visual")
	FVector2D SlotGrid = FVector2D(1, 1);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Activate")
	TSubclassOf<UGameplayEffect> AddGameplayEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Activate")
	TSubclassOf <UGameplayAbility> AddGameplayAbility;





};
