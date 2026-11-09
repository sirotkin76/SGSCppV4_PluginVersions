// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "EdGraph/EdGraphNode.h"
#include "Graph/Nodes/SGSCppCustomGraphAssetEditorNode.h"
#include "SGSCppCustomGraphAssetEditorNodeStart.generated.h"

UCLASS()
class USGSCppCustomGraphAssetEditorNodeStart : public USGSCppCustomGraphAssetEditorNode {
    GENERATED_BODY()

public: // USGSCppCustomGraphStartGraphNode interface
    virtual FText GetNodeTitle(ENodeTitleType::Type titalType) const override { return FText::FromString("Start"); }
    virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor::Red); }
    virtual bool CanUserDeleteNode() const override { return false; }

public: // USGSCppCustomGraphGraphNodeBase interface
    virtual UEdGraphPin* CreateSGSCppCustomGraphPin(EEdGraphPinDirection direction, FName name) override;

    virtual ESGSCppV4_CustomGraphNodeType GetSGSCppCustomGraphNodeType() const override { return ESGSCppV4_CustomGraphNodeType::StartNode; }
};
