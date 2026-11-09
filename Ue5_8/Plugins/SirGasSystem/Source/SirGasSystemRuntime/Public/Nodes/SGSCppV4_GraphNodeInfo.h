// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SGSCppV4_CustomGraphNodeType.h"
#include "SGSCppV4_GraphNodeInfo.generated.h"

class USGSCppCustomGraphRuntimeNode;

UENUM()
enum class ETypeOutputTagNodes
{
    OnShowResponse,
    OffShowResponse
  };


UCLASS(BlueprintType)
class SIRGASSYSTEMRUNTIME_API USGSCppV4_GraphNodeInfo : public UObject {
    GENERATED_BODY()
    
public:
    UPROPERTY()
    class USGSCppV4_CustomGraphAsset* _workingAssetV2;

    // В ноде енд, скрыл выходные параметры через эту переменную. В целом нужна только для нод Continue
    UPROPERTY()
    ETypeOutputTagNodes TypeOutputTagNodes = ETypeOutputTagNodes::OffShowResponse;

    UPROPERTY(EditAnywhere, Category = "SGSCppGraph|00_Attr")
    FText Title;

    UPROPERTY(EditAnywhere, Category = "SGSCppGraph|00_Attr")
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SGSCppGraph|00_Attr", meta = (Categories = "SGSCppGraph.Output", EditCondition = "TypeOutputTagNodes==ETypeOutputTagNodes::OnShowResponse", EditConditionHides ))
    TArray<FGameplayTag> OutputTags;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SGSCppGraph|00_Attr")
    int32 UniqueIndexNodeInGraph;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SGSCppGraph|00_Attr")
    ESGSCppV4_CustomGraphNodeType NodeType;
    
    /// ----------------------------------------------------------

    UFUNCTION(BlueprintPure, Category="SGSCppGraph")
    FText  GetSGSCppTitle()
    {
        return Title;
    };
    
    UFUNCTION(BlueprintPure, Category="SGSCppGraph")
    FText  GetSGSCppSGSCppCustomGraphText()
    {
        return Description;
    };

    UFUNCTION(BlueprintPure, Category="SGSCppGraph" )
    TArray<FGameplayTag> GetSGSCppOutputPins()
    {
        return OutputTags;
    };

    UFUNCTION(BlueprintCallable, Category = "SGSCppGraph", meta = (GameplayTagFilter = "SGSCppGraph.Output"))
    USGSCppCustomGraphRuntimeNode* GetSGSCppOutputNode(FGameplayTag InInputTag, USGSCppCustomGraphRuntimeNode* SGSCppCustomGraphRuntimeNode);

    UFUNCTION()
    void UpdateUniquIndex();
};
