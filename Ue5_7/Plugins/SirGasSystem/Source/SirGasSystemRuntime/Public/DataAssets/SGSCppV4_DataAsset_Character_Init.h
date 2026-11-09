// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SGSCppV4_DataAsset_Attr.h"
#include "Abilities/SGSCppV4_GameplayAbility.h"
#include "SGSCppV4_DataAsset_Character_Init.generated.h"



/**
 * 
 */
UCLASS()
class SIRGASSYSTEMRUNTIME_API USGSCppV4_DataAsset_Attr_Character_Init : public USGSCppV4_DataAsset_Attr
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FSGSCpp")
	TArray<TSubclassOf<UGameplayAbility>> GameplayAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FSGSCpp")
	TArray<TSubclassOf<UGameplayEffect>> GameplayEffects;

	
	/** Type of this item, set in native parent class 	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FSGSCpp|Animmontages")
	TArray<UAnimMontage *> arrAttackLight;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FSGSCpp|Animmontages")
	TArray<UAnimMontage *> arrAttackSpec;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FSGSCpp|Animmontages")
	TArray<UAnimMontage *> arrAttackHeavy;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FSGSCpp|Animmontages")
	TArray<UAnimMontage *> arrHits;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FSGSCpp|Animmontages")
	TArray<UAnimMontage *> arrSpawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FSGSCpp|Animmontages")
	TArray<UAnimMontage *> arrDead;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FSGSCpp|Animmontages")
	TArray<UAnimMontage *> arrStun;
 	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FSGSCpp|Animmontages")
	TMap<FName, UAnimMontage *> arrOthers;
 
	// UFUNCTIONS
	UFUNCTION(BlueprintPure, Category = "FSGSCpp|Getter")
	UAnimMontage * SGSCppFindArrAnimMontage(FName FindNameInArr);
};
