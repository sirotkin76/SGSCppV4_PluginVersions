// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SGSCppV4_GraphNodeInfoContinue.h"
#include "SGSCppV4_GraphNodeInfoContinueDA.generated.h"

// class USGSCppCustomGraphRuntimeNode;

UCLASS(BlueprintType)
class SIRGASSYSTEMRUNTIME_API USGSCppV4_GraphNodeInfoContinueDA : public USGSCppV4_GraphNodeInfoContinue {

    GENERATED_BODY()
    
public:

    //
    UPROPERTY(EditAnywhere, Category = "SGSCppGraph|01_AttrNodeContinue")
    FPrimaryAssetId SGSCppDataAssetAttrV3;

    UFUNCTION()
    FPrimaryAssetId GetSGSCppDataAsset();
    
    // 
    UFUNCTION()
    USGSCppV4_DataAsset_Attr * GetSGSCppCastSGSCppDataAssetAttrV3();


    UFUNCTION()
    UPrimaryDataAsset * GetSGSCppCastPrimaryDataAsset();

};
