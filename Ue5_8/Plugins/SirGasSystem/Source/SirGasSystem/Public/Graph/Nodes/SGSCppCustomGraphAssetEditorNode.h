// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "EdGraph/EdGraphNode.h"
#include "Nodes/SGSCppV4_CustomGraphNodeType.h"
#include "Nodes/SGSCppV4_GraphNodeInfo.h"
#include "SGSCppCustomGraphAssetEditorNode.generated.h"

UCLASS()
class USGSCppCustomGraphAssetEditorNode : public UEdGraphNode {
    GENERATED_BODY()

public: // Our interface
    
    UPROPERTY()
    USGSCppV4_CustomGraphAsset* _workingAsset;

    UPROPERTY()
    int32 UniqueIndexNodeInGraphCustomGraph;
    
    virtual UEdGraphPin* CreateSGSCppCustomGraphPin(EEdGraphPinDirection direction, FName name) { /* Must be overidden */ return nullptr; };
    virtual UEdGraphPin* CreateDefaultInputPin() { return nullptr; }
    virtual void CreateDefaultOutputPins() { /* Nothing to do by default */ }

    virtual void InitNodeInfo(UObject* outer) { /* None by default */ }
    virtual void SetNodeInfo(USGSCppV4_GraphNodeInfo* nodeInfo) { /* None by default */ }
    virtual USGSCppV4_GraphNodeInfo* GetNodeInfo() const { /* None by default */ return nullptr; }

    virtual ESGSCppV4_CustomGraphNodeType GetSGSCppCustomGraphNodeType() const { return ESGSCppV4_CustomGraphNodeType::Unknown; }

    virtual void OnPropertiesChanged() { /* Nothing to do by default */ }
};
