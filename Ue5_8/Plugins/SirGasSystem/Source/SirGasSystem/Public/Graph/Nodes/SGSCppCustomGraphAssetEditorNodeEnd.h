// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "EdGraph/EdGraphNode.h"
#include "Nodes/USGSCppV4_CustomGraphRuntimeInfoNodeEnd.h"
#include "SGSCppCustomGraphAssetEditorNode.h"
#include "SGSCppCustomGraphAssetEditorNodeEnd.generated.h"

UCLASS(BlueprintType)
class USGSCppCustomGraphAssetEditorNodeEnd : public USGSCppCustomGraphAssetEditorNode {
    GENERATED_BODY()

public: // USGSCppCustomGraphStartGraphNode interface
    virtual FText GetNodeTitle(ENodeTitleType::Type titalType) const override;
    virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor::Blue); }
    virtual bool CanUserDeleteNode() const override { return true; }
    virtual void GetNodeContextMenuActions(class UToolMenu* menu, class UGraphNodeContextMenuContext* context) const override;

public: // USGSCppCustomGraphGraphNodeBase interface
    virtual UEdGraphPin* CreateSGSCppCustomGraphPin(EEdGraphPinDirection direction, FName name) override;
    virtual UEdGraphPin* CreateDefaultInputPin() override; 

    virtual void InitNodeInfo(UObject* outer)
    {
        _nodeInfo = NewObject<USGSCppV4_CustomGraphRuntimeInfoNodeEnd>(outer);
        
        UniqueIndexNodeInGraphCustomGraph = GetUniqueID();
        _nodeInfo->UniqueIndexNodeInGraph = UniqueIndexNodeInGraphCustomGraph;
        
        _nodeInfo->_workingAssetV2 = _workingAsset;
        _nodeInfo->NodeType = GetSGSCppCustomGraphNodeType();
        
    }
    
    virtual void SetNodeInfo(USGSCppV4_GraphNodeInfo* nodeInfo) override
    {
        _nodeInfo = Cast<USGSCppV4_CustomGraphRuntimeInfoNodeEnd>(nodeInfo);
    }
    
    virtual USGSCppV4_GraphNodeInfo* GetNodeInfo() const override
    {
        return _nodeInfo;
    }

    virtual ESGSCppV4_CustomGraphNodeType GetSGSCppCustomGraphNodeType() const override
    {
        return ESGSCppV4_CustomGraphNodeType::EndNode;
    }

   virtual void OnPropertiesChanged()
    {
        Modify();
    } 

protected:
    UPROPERTY()
    class USGSCppV4_CustomGraphRuntimeInfoNodeEnd* _nodeInfo = nullptr;
};
