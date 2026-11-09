// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "EdGraph/EdGraphNode.h"
#include "Graph/Nodes/SGSCppCustomGraphAssetEditorNode.h"
#include "Nodes/SGSCppV4_GraphNodeInfoContinueDA.h"
#include "Nodes/SGSCppV4_CustomGraphNodeType.h"
#include "SGSCppCustomGraphAssetEditorNodeContinueDataAsset.generated.h"

UCLASS(BlueprintType)
class USGSCppCustomGraphAssetEditorNodeContinueDataAsset : public USGSCppCustomGraphAssetEditorNode {
    GENERATED_BODY()

public: // UEdGraphNode interface
    virtual FText GetNodeTitle(ENodeTitleType::Type titalType) const override;
    virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor::Green); }
    virtual bool CanUserDeleteNode() const override { return true; }
    virtual void GetNodeContextMenuActions(class UToolMenu* menu, class UGraphNodeContextMenuContext* context) const override;

public: // USGSCppCustomGraphGraphNodeBase interface
    
    
    virtual UEdGraphPin* CreateSGSCppCustomGraphPin(EEdGraphPinDirection direction, FName name) override;
    virtual UEdGraphPin* CreateDefaultInputPin() override;
    virtual void CreateDefaultOutputPins() override;

    virtual ESGSCppV4_CustomGraphNodeType GetSGSCppCustomGraphNodeType() const override { return ESGSCppV4_CustomGraphNodeType::SGSCppNodeContinueDataAsset; }

    virtual void OnPropertiesChanged()
    {
        SyncPinsWithResponses();
    }

public: // Our interface
    void SyncPinsWithResponses();

    USGSCppV4_GraphNodeInfoContinueDA* GetSGSCppCustomGraphNodeInfo()
    {
        return _nodeInfo;
    }
    
    virtual void InitNodeInfo(UObject* outer)
    {
        _nodeInfo = NewObject<USGSCppV4_GraphNodeInfoContinueDA>(outer);

        UniqueIndexNodeInGraphCustomGraph = GetUniqueID();
        _nodeInfo->UniqueIndexNodeInGraph = UniqueIndexNodeInGraphCustomGraph;
        
        _nodeInfo->_workingAssetV2 = _workingAsset;
        _nodeInfo->NodeType = GetSGSCppCustomGraphNodeType();
        
    }
    
    virtual void SetNodeInfo(USGSCppV4_GraphNodeInfo* nodeInfo) override
    {
        _nodeInfo = Cast<USGSCppV4_GraphNodeInfoContinueDA>(nodeInfo);
    }
    
    virtual USGSCppV4_GraphNodeInfo* GetNodeInfo() const override
    {
        return _nodeInfo;
    }

protected:

    UPROPERTY()
    USGSCppV4_GraphNodeInfoContinueDA* _nodeInfo = nullptr;

};
