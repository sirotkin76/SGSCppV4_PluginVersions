// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SGSCppV4_GraphNodeInfoContinue.h"
#include "Templates/SubclassOf.h"
#include "SGSCppV4_GraphNodeInfoContinueCD.generated.h"

UCLASS(BlueprintType)
class SIRGASSYSTEMRUNTIME_API USGSCppV4_GraphNodeInfoContinueCD : public USGSCppV4_GraphNodeInfoContinue {
    
    GENERATED_BODY()

public:
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SGSCppGraph|02_AttrNodeContinue")
    TMap<FName, int32> ArrInt32;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SGSCppGraph|02_AttrNodeContinue")
    TMap<FName, FText> ArrText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SGSCppGraph|02_AttrNodeContinue")
    TMap<FName, FName> ArrName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SGSCppGraph|02_AttrNodeContinue")
    TMap <FName, TSoftObjectPtr<UObject>> ArrUObject;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SGSCppGraph|02_AttrNodeContinue")
    TMap <FName, TSubclassOf<UObject>> ArrClassUObject;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SGSCppGraph|02_AttrNodeContinue")
    TMap <FName, float> ArrFloat;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SGSCppGraph|02_AttrNodeContinue")
    TMap <FName, FGameplayTagContainer> ArrGameplayTags;

	
    // UFUNCTIONS
    UFUNCTION(BlueprintPure, Category = "SGSCppGraph|Getter")
    int32 SGSCppFindArrInt(FName FindNameInArr);

    UFUNCTION(BlueprintPure, Category = "SGSCppGraph|Getter")
    float SGSCppFindArrFloat(FName FindNameInArr);

    UFUNCTION(BlueprintPure, Category = "SGSCppGraph|Getter")
    FText SGSCppFindArrText(FName FindNameInArr);

    UFUNCTION(BlueprintPure, Category = "SGSCppGraph|Getter")
    FName SGSCppFindArrName(FName FindNameInArr);

    UFUNCTION(BlueprintPure, Category = "SGSCppGraph|Getter")
    TSoftObjectPtr<UObject> SGSCppFindArrUObject(FName FindNameInArr);

    UFUNCTION(BlueprintPure, Category = "SGSCppGraph|Getter")
    TSubclassOf<UObject> SGSCppFindArrClassUObject(FName FindNameInArr);

    UFUNCTION(BlueprintPure, Category = "SGSCppAbilityInfo|Getter")
    FGameplayTagContainer SGSCppFindArrGameplayTags(FName FindNameInArr);
};
