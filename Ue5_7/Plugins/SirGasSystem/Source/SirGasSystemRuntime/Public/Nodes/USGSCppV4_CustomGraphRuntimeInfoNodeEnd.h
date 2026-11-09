// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "SGSCppV4_GraphNodeInfo.h"
#include "USGSCppV4_CustomGraphRuntimeInfoNodeEnd.generated.h"

UCLASS(BlueprintType)
class SIRGASSYSTEMRUNTIME_API USGSCppV4_CustomGraphRuntimeInfoNodeEnd : public USGSCppV4_GraphNodeInfo {

    GENERATED_BODY()

public:
    //USGSCppV4_CustomGraphRuntimeInfoNodeEnd();

    // Игрок сам может определять конечный результат и составлять через switch Логику для ноды
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SGSCppGraph|01_AttrNodeEnd", meta = (ToolTip = "This variable will help you specify what logic you want to execute in your Blueprints when the value of this variable is received."))
    FString CustomAction = TEXT("");

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SGSCppGraph|JumpSection", meta = ( EditCondition = "Action == ESGSCppCustomGraphNodeAction::JumpOnNewNodeUseTag", Categories = "SGSCppGraph.Location"))
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SGSCppGraph|01_AttrNodeEnd", meta = (Categories = "SGSCppGraph.Location", ToolTip = "Specify a unique tag to search for a node with this tag."))
    FGameplayTag TagForFindNode;

    UPROPERTY(EditAnywhere, Category = "SGSCppGraph|01_AttrNodeEnd")
    FPrimaryAssetId CustomDataAsset;

    UFUNCTION(BlueprintPure, Category="SGSCppGraph")
    FString GetSGSCppActionData() { return CustomAction; }; 

    UFUNCTION(BlueprintPure, Category = "SGSCppGraph")
    UPrimaryDataAsset* SGSCppGetCustomDataAsset();



    /*
    public:
    meta=(ConsoleVariable="r.Shadow.Funky")
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SGSCppGraph|JumpSection", meta = (EditCondition = "Action == ESGSCppCustomGraphNodeAction::JumpOnNewNodeUseDataAsset"))
    FPrimaryAssetId SGSCppDataAssetForFindNode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SGSCppGraph|Attr")
    UPrimaryDataAsset * PrimaryDataAssetEndNode; 
    */

    /*
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SGSCppGraph|Attr")
    ESGSCppCustomGraphNodeAction Action = ESGSCppCustomGraphNodeAction::None;
    
    UFUNCTION(BlueprintPure, Category="SGSCppGraph")
    ESGSCppCustomGraphNodeAction GetSGSCppEnumAction() { return Action; }; 
    */
    
    /*
    UFUNCTION(BlueprintPure, Category="SGSCppGraph")
    UPrimaryDataAsset * GetSGSCppPrimaryDataAssetEndNode() {return PrimaryDataAssetEndNode; };
    */
};
