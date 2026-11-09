
// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#include "Graph/SGSCppCustomGraphAssetEditorApp.h"
#include "Graph/SGSCppV4_CustomGraphAsset.h"

#include "Kismet2/BlueprintEditorUtils.h"
#include "Graph/SGSCppCustomGraphAssetAppMode.h"
#include "Graph/SGSCppCustomGraphGraphSchema.h"

#include "Graph/Nodes/SGSCppCustomGraphAssetEditorNode.h"
#include "Graph/Nodes/SGSCppCustomGraphAssetEditorNodeContinueCustomData.h"
#include "Graph/Nodes/SGSCppCustomGraphAssetEditorNodeStart.h"
#include "Graph/Nodes/SGSCppCustomGraphAssetEditorNodeEnd.h"
#include "Graph/Nodes/SGSCppCustomGraphAssetEditorNodeContinueDataAsset.h"


DEFINE_LOG_CATEGORY_STATIC(SGSCppCustomGraphAssetEditorAppSub, Log, All);

void SGSCppCustomGraphAssetEditorApp::RegisterTabSpawners(const TSharedRef<class FTabManager>& tabManager) {
    FWorkflowCentricApplication::RegisterTabSpawners(tabManager);
}

void SGSCppCustomGraphAssetEditorApp::InitEditor(const EToolkitMode::Type mode, const TSharedPtr<class IToolkitHost>& initToolkitHost, UObject* inObject) {
	TArray<UObject*> objectsToEdit;
    objectsToEdit.Add(inObject);
    
    _workingAsset = Cast<USGSCppV4_CustomGraphAsset>(inObject);
    _workingAsset->SetPreSaveListener([this] () { OnWorkingAssetPreSave(); });

    _workingGraph = FBlueprintEditorUtils::CreateNewGraph(
        _workingAsset,
        NAME_None,
        UEdGraph::StaticClass(),
        USGSCppCustomGraphGraphSchema::StaticClass()
    );

	InitAssetEditor( 
        mode, 
        initToolkitHost, 
        TEXT("SGSCppCustomGraphAssetEditor"), 
        FTabManager::FLayout::NullLayout, 
        true, // createDefaultStandaloneMenu 
        true,  // createDefaultToolbar
        objectsToEdit);

    // Add our modes (just one for this example)
    AddApplicationMode(TEXT("SGSCppCustomGraphAssetAppMode"), MakeShareable(new SGSCppCustomGraphAssetAppMode(SharedThis(this))));

    // Set the mode
    SetCurrentMode(TEXT("SGSCppCustomGraphAssetAppMode"));

    UpdateEditorGraphFromWorkingAsset();
}

void SGSCppCustomGraphAssetEditorApp::OnClose() {
    UpdateWorkingAssetFromGraph();
    _workingAsset->SetPreSaveListener(nullptr);
    FAssetEditorToolkit::OnClose();
}

void SGSCppCustomGraphAssetEditorApp::OnNodeDetailViewPropertiesUpdated(const FPropertyChangedEvent& event) {
    if (_workingGraphUi != nullptr) {
        // Get the node being modified
        USGSCppCustomGraphAssetEditorNode* SGSCppCustomGraphNode = GetSelectedNode(_workingGraphUi->GetSelectedNodes());
        if (SGSCppCustomGraphNode != nullptr) {
            SGSCppCustomGraphNode->OnPropertiesChanged();
        }
        _workingGraphUi->NotifyGraphChanged();
    }
}

void SGSCppCustomGraphAssetEditorApp::OnWorkingAssetPreSave() {
    // Update our asset from the graph just before saving it
    UpdateWorkingAssetFromGraph();
}

void SGSCppCustomGraphAssetEditorApp::UpdateWorkingAssetFromGraph() {
    if (_workingAsset == nullptr || _workingGraph == nullptr) {
        return;
    }

    USGSCppV4_CustomGraphRuntimeGraph* runtimeGraph = NewObject<USGSCppV4_CustomGraphRuntimeGraph>(_workingAsset);
    _workingAsset->Graph = runtimeGraph;

    TArray<std::pair<FGuid, FGuid>> connections;
    TMap<FGuid, USGSCppCustomGraphRuntimePin*> idToPinMap;

    for (UEdGraphNode* uiNode : _workingGraph->Nodes) {
        USGSCppCustomGraphRuntimeNode* runtimeNode = NewObject<USGSCppCustomGraphRuntimeNode>(runtimeGraph);
        runtimeNode->Position = FVector2D(uiNode->NodePosX, uiNode->NodePosY);

        for (UEdGraphPin* uiPin : uiNode->Pins) {
            USGSCppCustomGraphRuntimePin* runtimePin = NewObject<USGSCppCustomGraphRuntimePin>(runtimeNode);
            runtimePin->PinName = uiPin->PinName;
            runtimePin->PinId = uiPin->PinId;
            runtimePin->Parent = runtimeNode;

            if (uiPin->HasAnyConnections() && uiPin->Direction == EEdGraphPinDirection::EGPD_Output) {
                std::pair<FGuid, FGuid> connection = std::make_pair(uiPin->PinId, uiPin->LinkedTo[0]->PinId);
                connections.Add(connection);
            }

            idToPinMap.Add(uiPin->PinId, runtimePin);
            if (uiPin->Direction == EEdGraphPinDirection::EGPD_Input) {
                runtimeNode->InputPin = runtimePin;
            } else {
                runtimeNode->OutputPins.Add(runtimePin);
            }
        }

        USGSCppCustomGraphAssetEditorNode* uiSGSCppCustomGraphNode = Cast<USGSCppCustomGraphAssetEditorNode>(uiNode);
        runtimeNode->NodeInfo = DuplicateObject(uiSGSCppCustomGraphNode->GetNodeInfo(), runtimeNode);
        runtimeNode->NodeType = uiSGSCppCustomGraphNode->GetSGSCppCustomGraphNodeType();

        runtimeGraph->Nodes.Add(runtimeNode);
    }

    for (std::pair<FGuid, FGuid> connection : connections) {
        USGSCppCustomGraphRuntimePin* pin1 = idToPinMap[connection.first];
        USGSCppCustomGraphRuntimePin* pin2 = idToPinMap[connection.second];
        pin1->Connection = pin2;
    };

    TArray<USGSCppCustomGraphRuntimeNode*> localNodes = _workingAsset->Graph->Nodes;
    
}

void SGSCppCustomGraphAssetEditorApp::UpdateEditorGraphFromWorkingAsset() {
    if (_workingAsset->Graph == nullptr) {
        USGSCppV4_CustomGraphRuntimeGraph* runtimeGraph = NewObject<USGSCppV4_CustomGraphRuntimeGraph>(_workingAsset);
        _workingGraph->GetSchema()->CreateDefaultNodesForGraph(*_workingGraph);
        return;
    }

    TArray<std::pair<FGuid, FGuid>> connections;
    TMap<FGuid, UEdGraphPin*> idToPinMap;

    for (USGSCppCustomGraphRuntimeNode* runtimeNode : _workingAsset->Graph->Nodes)
    {
        USGSCppCustomGraphAssetEditorNode* newNode = nullptr;
        
        if (runtimeNode->NodeType == ESGSCppV4_CustomGraphNodeType::StartNode) {
            newNode = NewObject<USGSCppCustomGraphAssetEditorNodeStart>(_workingGraph);
        } else
            if (runtimeNode->NodeType == ESGSCppV4_CustomGraphNodeType::SGSCppNodeContinueDataAsset) {
            newNode = NewObject<USGSCppCustomGraphAssetEditorNodeContinueDataAsset>(_workingGraph);
        } else
        if (runtimeNode->NodeType == ESGSCppV4_CustomGraphNodeType::EndNode) {
        newNode = NewObject<USGSCppCustomGraphAssetEditorNodeEnd>(_workingGraph);
        } else
        if (runtimeNode->NodeType == ESGSCppV4_CustomGraphNodeType::SGSCppCustomGraphNodeCustomData) {
            newNode = NewObject<USGSCppCustomGraphAssetEditorNodeContinueCustomData>(_workingGraph);
        }
        else {
            UE_LOG(SGSCppCustomGraphAssetEditorAppSub, Error, TEXT("SGSCppCustomGraphAssetEditorApp::UpdateEditorGraphFromWorkingAsset: Unknown node type"));
            continue;
        }
        
        newNode->CreateNewGuid();
        newNode->NodePosX = runtimeNode->Position.X;
        newNode->NodePosY = runtimeNode->Position.Y;
        newNode->_workingAsset = _workingAsset;
        //runtimeNode->GetSGSCppNodeInfo()->UniqueIndexNodeInGraph
        
        //newNode->CreateUniquePinName(newNode->GetNodeInfo()->UniquePinName);
        
        if (runtimeNode->NodeInfo != nullptr) {
            newNode->SetNodeInfo(DuplicateObject(runtimeNode->NodeInfo, newNode));
        } else {
            newNode->InitNodeInfo(newNode);
        }

        if (runtimeNode->InputPin != nullptr) {
            USGSCppCustomGraphRuntimePin* pin = runtimeNode->InputPin;
            UEdGraphPin* uiPin = newNode->CreateSGSCppCustomGraphPin(EEdGraphPinDirection::EGPD_Input, pin->PinName);
            uiPin->PinId = pin->PinId;

            if (pin->Connection != nullptr) {
                connections.Add(std::make_pair(pin->PinId, pin->Connection->PinId));
            }
            idToPinMap.Add(pin->PinId, uiPin);
        }

        for (USGSCppCustomGraphRuntimePin* pin : runtimeNode->OutputPins) {
            UEdGraphPin* uiPin = newNode->CreateSGSCppCustomGraphPin(EEdGraphPinDirection::EGPD_Output, pin->PinName);
            uiPin->PinId = pin->PinId;

            if (pin->Connection != nullptr) {
                connections.Add(std::make_pair(pin->PinId, pin->Connection->PinId));
            }
            idToPinMap.Add(pin->PinId, uiPin);
        }

        _workingGraph->AddNode(newNode, true, true);
        
    }

    for (std::pair<FGuid, FGuid> connection : connections) {
        UEdGraphPin* fromPin = idToPinMap[connection.first];
        UEdGraphPin* toPin = idToPinMap[connection.second];
        fromPin->LinkedTo.Add(toPin);
        toPin->LinkedTo.Add(fromPin);
    }
}

/**
 * Returns the first USGSCppCustomGraphGraphNode in the given selection or nullptr if there are none.
 */
USGSCppCustomGraphAssetEditorNode* SGSCppCustomGraphAssetEditorApp::GetSelectedNode(const FGraphPanelSelectionSet& selection) {
    for (UObject* obj : selection) {
        USGSCppCustomGraphAssetEditorNode* node = Cast<USGSCppCustomGraphAssetEditorNode>(obj);
        if (node != nullptr) {
            return node;
        }
    }

    return nullptr;
}

void SGSCppCustomGraphAssetEditorApp::SetSelectedNodeDetailView(TSharedPtr<class IDetailsView> detailsView) { 
    _selectedNodeDetailView = detailsView;
    _selectedNodeDetailView->OnFinishedChangingProperties().AddRaw(this, &SGSCppCustomGraphAssetEditorApp::OnNodeDetailViewPropertiesUpdated);
}

void SGSCppCustomGraphAssetEditorApp::OnGraphSelectionChanged(const FGraphPanelSelectionSet& selection) {
    USGSCppCustomGraphAssetEditorNode* selectedNode = GetSelectedNode(selection);
    if (selectedNode != nullptr) {
        _selectedNodeDetailView->SetObject(selectedNode->GetNodeInfo());
    } else {
        _selectedNodeDetailView->SetObject(nullptr);
    }
}
