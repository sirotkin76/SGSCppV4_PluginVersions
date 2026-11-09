// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#include "Graph/SGSCppCustomGraphGraphSchema.h"
#include "Graph/Nodes/SGSCppCustomGraphAssetEditorNode.h"
#include "Graph/Nodes/SGSCppCustomGraphAssetEditorNodeContinueDataAsset.h"
#include "Graph/Nodes/SGSCppCustomGraphAssetEditorNodeStart.h"
#include "Graph/Nodes/SGSCppCustomGraphAssetEditorNodeEnd.h"
#include "Graph/Nodes/SGSCppCustomGraphAssetEditorNodeContinueCustomData.h"

void USGSCppCustomGraphGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& contextMenuBuilder) const {
    TSharedPtr<FNewNodeAction> newSGSCppCustomGraphNodeAction(
        new FNewNodeAction(
            USGSCppCustomGraphAssetEditorNodeContinueDataAsset::StaticClass(),
            FText::FromString(TEXT("Nodes")),
            FText::FromString(TEXT("New Continue_DataAsset Node")),
            FText::FromString(TEXT("Makes a new Continue_DataAsset node")),
            0
        )
    );
    
    TSharedPtr<FNewNodeAction> newSGSCppCustomGraphNodeActionData(
        new FNewNodeAction(
            USGSCppCustomGraphAssetEditorNodeContinueCustomData::StaticClass(),
            FText::FromString(TEXT("Nodes")),
            FText::FromString(TEXT("New Continue_CustomData Node")),
            FText::FromString(TEXT("Makes a new Continue_CustomData node")),
            0
        )
    );

    TSharedPtr<FNewNodeAction> newEndNodeAction(
        new FNewNodeAction(
            USGSCppCustomGraphAssetEditorNodeEnd::StaticClass(),
            FText::FromString(TEXT("Nodes")),
            FText::FromString(TEXT("New End Node")),
            FText::FromString(TEXT("Makes a new end node")),
            0
        )
    );

    contextMenuBuilder.AddAction(newSGSCppCustomGraphNodeActionData);
    contextMenuBuilder.AddAction(newSGSCppCustomGraphNodeAction);
    contextMenuBuilder.AddAction(newEndNodeAction);
}

const FPinConnectionResponse USGSCppCustomGraphGraphSchema::CanCreateConnection(const UEdGraphPin* a, const UEdGraphPin* b) const {
    if (a == nullptr || b == nullptr) {
        return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Need 2 pins"));
    }

    if (a->Direction == b->Direction) {
        return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Inputs can only connect to outputs"));
    }

    return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_AB, TEXT(""));
}

void USGSCppCustomGraphGraphSchema::CreateDefaultNodesForGraph(UEdGraph& graph) const {
    USGSCppCustomGraphAssetEditorNodeStart* startNode = NewObject<USGSCppCustomGraphAssetEditorNodeStart>(&graph);
    startNode->CreateNewGuid();
    startNode->NodePosX = 0;
    startNode->NodePosY = 0;

    startNode->CreateSGSCppCustomGraphPin(EEdGraphPinDirection::EGPD_Output, FName(TEXT("Start")));
    
    graph.AddNode(startNode, true, true);
    graph.Modify();
}

UEdGraphNode* FNewNodeAction::PerformAction(UEdGraph* parentGraph, UEdGraphPin* fromPin, const FVector2D location, bool bSelectNewNode) {
    USGSCppCustomGraphAssetEditorNode* result = NewObject<USGSCppCustomGraphAssetEditorNode>(parentGraph, _classTemplate);
    result->CreateNewGuid();
    result->NodePosX = location.X;
    result->NodePosY = location.Y;
    result->InitNodeInfo(result);
    
    UEdGraphPin* inputPin = result->CreateDefaultInputPin();
    result->CreateDefaultOutputPins();

    if (fromPin != nullptr) {
        result->GetSchema()->TryCreateConnection(fromPin, inputPin);
    }

    parentGraph->Modify();
    parentGraph->AddNode(result, true, true);

    return result;
}
