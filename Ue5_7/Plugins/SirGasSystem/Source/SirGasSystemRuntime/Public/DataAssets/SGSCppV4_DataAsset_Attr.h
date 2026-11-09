// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NativeGameplayTags.h"
#include "SGSCppV4_DataAsset_Attr.generated.h"

/**
 *
 */
UCLASS()
class SIRGASSYSTEMRUNTIME_API USGSCppV4_DataAsset_Attr : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	USGSCppV4_DataAsset_Attr();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SGSCppAbilityInfo|Arr")
	TMap<FName, bool> ArrBool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SGSCppAbilityInfo|Arr")
	TMap<FName, int32> ArrInt32;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SGSCppAbilityInfo|Arr")
	TMap <FName, float> ArrFloat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SGSCppAbilityInfo|Arr")
	TMap<FName, FText> ArrText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SGSCppAbilityInfo|Arr")
	TMap<FName, FName> ArrName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SGSCppAbilityInfo|Arr")
	TMap<FName, FString> ArrString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SGSCppAbilityInfo|Arr")
	TMap <FName, TSoftObjectPtr<UObject>> ArrUObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SGSCppAbilityInfo|Arr")
	TMap <FName, TSubclassOf<UObject>> ArrClassUObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SGSCppAbilityInfo|Arr")
	TMap <FName, FGameplayTagContainer> ArrGameplayTags;

	
	// UFUNCTIONS
	UFUNCTION(BlueprintPure, Category = "SGSCppAbilityInfo|Getter")
	bool SGSCppFindArrBool(FName FindNameInArr);
	
	UFUNCTION(BlueprintPure, Category = "SGSCppAbilityInfo|Getter")
	int32 SGSCppFindArrInt(FName FindNameInArr);

	UFUNCTION(BlueprintPure, Category = "SGSCppAbilityInfo|Getter")
	float SGSCppFindArrFloat(FName FindNameInArr);

	UFUNCTION(BlueprintPure, Category = "SGSCppAbilityInfo|Getter")
	FText SGSCppFindArrText(FName FindNameInArr);

	UFUNCTION(BlueprintPure, Category = "SGSCppAbilityInfo|Getter")
	FName SGSCppFindArrName(FName FindNameInArr);

	UFUNCTION(BlueprintPure, Category = "SGSCppAbilityInfo|Getter")
	FString SGSCppFindArrString(FName FindNameInArr);

	UFUNCTION(BlueprintPure, Category = "SGSCppAbilityInfo|Getter")
	TSoftObjectPtr<UObject> SGSCppFindArrUObject(FName FindNameInArr);

	UFUNCTION(BlueprintPure, Category = "SGSCppAbilityInfo|Getter")
	TSubclassOf<UObject> SGSCppFindArrClassUObject(FName FindNameInArr);

	UFUNCTION(BlueprintPure, Category = "SGSCppAbilityInfo|Getter")
	FGameplayTagContainer SGSCppFindArrGameplayTags(FName FindNameInArr);
};
