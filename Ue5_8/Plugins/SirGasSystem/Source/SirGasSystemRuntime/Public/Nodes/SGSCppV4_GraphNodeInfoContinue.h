// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SGSCppV4_GraphNodeInfo.h"
#include "SGSCppV4_GraphNodeInfoContinue.generated.h"

// class USGSCppCustomGraphRuntimeNode;

UCLASS(BlueprintType)
class SIRGASSYSTEMRUNTIME_API USGSCppV4_GraphNodeInfoContinue : public USGSCppV4_GraphNodeInfo {

    GENERATED_BODY()
    
public:
    USGSCppV4_GraphNodeInfoContinue(const FObjectInitializer& objectInitializer);

    
    // Данный тег нужен для поиска текущего положения в графе
    UPROPERTY(EditAnywhere, Category = "SGSCppGraph|01_AttrNodeContinue", meta = (Categories = "SGSCppGraph.Location")) // , EditCondition = "Action == ESGSCppCustomGraphNodeAction::JumpOnNewNodeUseDataAsset"
    FGameplayTag UniqueTagToSearchForThisNode;

};
