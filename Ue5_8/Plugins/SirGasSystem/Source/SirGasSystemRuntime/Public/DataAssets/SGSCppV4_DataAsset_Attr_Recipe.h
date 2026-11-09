// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Data/SGSCppV4_Struct.h"
#include "SGSCppV4_DataAsset_Attr.h"

#include "SGSCppV4_DataAsset_Attr_Recipe.generated.h"

class USGSCppV4_DataAsset_Attr_InventorySlot;
/**
 * 
 */
UCLASS(Blueprintable, Category = "SGSCpp|BFL")
class SIRGASSYSTEMRUNTIME_API USGSCppV4_DataAsset_Attr_Recipe : public USGSCppV4_DataAsset_Attr
{
	GENERATED_BODY()

public:
	
	USGSCppV4_DataAsset_Attr_Recipe();
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Create")
	TSoftObjectPtr<USGSCppV4_DataAsset_Attr_Recipe> CreateNewRecipe;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	UTexture2D* Icon;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	bool OneTimePrescription;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	bool UpgradeLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 1, Min = 1))
	float Time = 0.0f;

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
	
	// Сообщение выводится, если данный рецепт не может выполняться.
	// This message is displayed if the given recipe cannot be executed.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Info")
	FString Error_Message;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	TArray<FName> InventorySlotTypes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	TArray<FName> InventorySlotSubType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FName FastSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	TSoftObjectPtr<USGSCppV4_DataAsset_Attr_Recipe> RequiredRecipeForActivateThisRecipe;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CreateSlot")
	FSGSCppV4_SlotCount SlotCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RecipeForCreateSlot")
	TArray<FSGSCppV4_SlotCount> arrSlotCount;

};
