// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NameTypes.h"
#include "Nodes/SGSCppV4_GraphNodeInfo.h"
#include "Nodes/SGSCppV4_CustomGraphNodeType.h"
#include "SGSCppV4_CustomGraphRuntimeGraph.generated.h"

class USGSCppCustomGraphRuntimePin;
struct FOutputData;

UCLASS(BlueprintType)
class SIRGASSYSTEMRUNTIME_API USGSCppCustomGraphRuntimePin : public UObject {
    GENERATED_BODY()
public:

    UPROPERTY(Category="SGSCppGraph", VisibleAnywhere, BlueprintReadOnly)
    FName PinName;

    UPROPERTY(Category="SGSCppGraph", VisibleAnywhere, BlueprintReadOnly)
    FGuid PinId;

    UPROPERTY(Category="SGSCppGraph", VisibleAnywhere, BlueprintReadOnly)
    USGSCppCustomGraphRuntimePin* Connection = nullptr;

    UPROPERTY(Category="SGSCppGraph", VisibleAnywhere, BlueprintReadOnly)
    USGSCppCustomGraphRuntimeNode* Parent = nullptr;

    UFUNCTION(BlueprintPure, Category = "SGSCppGraph")
    USGSCppCustomGraphRuntimeNode* GetSGSCppConnectionNode() { return Connection->Parent; };

};

UCLASS(BlueprintType)
class SIRGASSYSTEMRUNTIME_API USGSCppCustomGraphRuntimeNode : public UObject {
    GENERATED_BODY()

public:

    UPROPERTY(Category = "SGSCppGraph", VisibleAnywhere, BlueprintReadOnly)
    ESGSCppV4_CustomGraphNodeType NodeType = ESGSCppV4_CustomGraphNodeType::SGSCppNodeContinueDataAsset;

    UPROPERTY(Category = "SGSCppGraph", VisibleAnywhere, BlueprintReadOnly)
    USGSCppCustomGraphRuntimePin* InputPin;

    UPROPERTY(Category = "SGSCppGraph", VisibleAnywhere, BlueprintReadOnly)
    TArray<USGSCppCustomGraphRuntimePin*> OutputPins;

    UPROPERTY()
    FVector2D Position;

    UPROPERTY()
    USGSCppV4_GraphNodeInfo* NodeInfo = nullptr;

    UPROPERTY()
    class USGSCppV4_CustomGraphRuntimeGraph* SGSCppV4_CustomGraphRuntimeGraph;

public:

    UFUNCTION(BlueprintPure, Category="SGSCppGraph")
    ESGSCppV4_CustomGraphNodeType GetSGSCppNodeType() { return NodeType; };

    UFUNCTION(BlueprintPure, Category="SGSCppGraph")
    USGSCppCustomGraphRuntimePin* GetSGSCppInputPin() {return InputPin; };
    
    UFUNCTION(BlueprintPure, Category="SGSCppGraph")
    TArray<USGSCppCustomGraphRuntimePin*> GetSGSCppOutputPins(){return OutputPins; };

    UFUNCTION(BlueprintPure, Category="SGSCppGraph")
    USGSCppV4_GraphNodeInfo* GetSGSCppNodeInfo() { return NodeInfo; };


    UFUNCTION(BlueprintCallable, Category = "SGSCppGraph")
    FOutputData GetSGSCppNodeVariables();

    /*
    UFUNCTION()
    FPrimaryAssetId GetSGSCppSGSCppDataAssetAttrV3() { return NodeInfo->GetSGSCppSGSCppDataAssetAttrV3(); };
    */

    UFUNCTION(BlueprintPure, Category = "SGSCppGraph")
    USGSCppV4_DataAsset_Attr * GetSGSCppCastSGSCppDataAssetAttrV3();

    UFUNCTION(BlueprintPure, Category = "SGSCppGraph")
    USGSCppCustomGraphRuntimeNode* GetSGSCppNextOutputNodeByPinIndex(int OutputPinIndex);

    UFUNCTION(BlueprintPure, Category = "SGSCppGraph", meta = (GameplayTagFilter = "SGSCppGraph.Output"))
    USGSCppCustomGraphRuntimeNode* GetSGSCppCheckTagAndGetParentNode(FGameplayTag InInputTag);

    UFUNCTION(BlueprintPure, Category = "SGSCppGraph")
    USGSCppV4_DataAsset_Attr * CheckNodeAndGetSGSCppDataAssetAttrV3(USGSCppV4_GraphNodeInfo* NodeInfoLocal);
    
};

UCLASS(BlueprintType)
class SIRGASSYSTEMRUNTIME_API USGSCppV4_CustomGraphRuntimeGraph : public UObject {

    GENERATED_BODY()

public:
    UPROPERTY()
    TArray<USGSCppCustomGraphRuntimeNode*> Nodes;

    UFUNCTION(BlueprintPure, Category = "SGSCppGraph")
    TArray<USGSCppCustomGraphRuntimeNode*>  GetSGSCppNodes() {return Nodes; };

    UFUNCTION(BlueprintPure, Category = "SGSCppGraph")
    USGSCppCustomGraphRuntimeNode * GetSGSCppGetNodeInArr(int32 i) { return GetSGSCppNodes()[i]; };

    UFUNCTION(meta = (GameplayTagFilter = "SGSCppGraph.Output"))
    USGSCppCustomGraphRuntimeNode* GetSGSCppFindNodeUseTag(FGameplayTag InInputTag);

};
