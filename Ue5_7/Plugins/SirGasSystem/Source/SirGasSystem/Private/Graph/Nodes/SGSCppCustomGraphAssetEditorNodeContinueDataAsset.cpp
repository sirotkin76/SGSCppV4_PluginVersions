// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#include "Graph/Nodes/SGSCppCustomGraphAssetEditorNodeContinueDataAsset.h"

#include "ToolMenu.h"
#include "Framework/Commands/UIAction.h"


FText USGSCppCustomGraphAssetEditorNodeContinueDataAsset::GetNodeTitle(ENodeTitleType::Type titalType) const { 
    USGSCppV4_GraphNodeInfo* nodeInfo = Cast<USGSCppV4_GraphNodeInfo>(_nodeInfo);

    FText localTitle = FText::FromString(TEXT("Node Continue_DataAsset"));
    
    if (nodeInfo->Title.IsEmpty()) {
        
        if (!nodeInfo->Description.IsEmpty())
        {
            FString SGSCppCustomGraphTextStr = nodeInfo->Description.ToString();
        
            if (SGSCppCustomGraphTextStr.Len() > 15) {
                SGSCppCustomGraphTextStr = SGSCppCustomGraphTextStr.Left(15) + TEXT("...");
            }
        
            return FText::FromString(SGSCppCustomGraphTextStr);
        }
        return localTitle;
    }
    return nodeInfo->Title;
}

void USGSCppCustomGraphAssetEditorNodeContinueDataAsset::GetNodeContextMenuActions(class UToolMenu* menu, class UGraphNodeContextMenuContext* context) const {
    FToolMenuSection& section = menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("SGSCppCustomGraph Node Actions")));

    USGSCppCustomGraphAssetEditorNodeContinueDataAsset* node = (USGSCppCustomGraphAssetEditorNodeContinueDataAsset*)this;
    
    /*
    section.AddMenuEntry(
        TEXT("AddPinEntry"),
        FText::FromString(TEXT("Add Response")),
        FText::FromString(TEXT("Creates a new response")),
        FSlateIcon(TEXT("SGSCppCustomGraphAssetEditorStyle"), TEXT("SGSCppCustomGraphAssetEditor.NodeAddPinIcon")),
        FUIAction(FExecuteAction::CreateLambda(
            [node] () {

                //node->GetSGSCppCustomGraphNodeInfo()->SGSCppCustomGraphResponses.Add(FText::FromString(TEXT("Response")));

                node->SyncPinsWithResponses();
                node->GetGraph()->NotifyGraphChanged();
                node->GetGraph()->Modify();
            }
        ))
    );
    */
    
    /*
    section.AddMenuEntry(
        
        TEXT("DeletePinEntry"),
        FText::FromString(TEXT("Delete the selected response")),
        FText::FromString(TEXT("Deletes the last response")),
        
        FSlateIcon(TEXT("SGSCppCustomGraphAssetEditorStyle"), TEXT("SGSCppCustomGraphAssetEditor.NodeDeletePinIcon")),
        FUIAction(FExecuteAction::CreateLambda(
            [node] () {
                
                UEdGraphPin* pin = node->GetPinAt(node->Pins.Num() - 1);
                
                if (pin->Direction != EEdGraphPinDirection::EGPD_Input) {
                    USGSCppCustomGraphRuntimeInfoNodeContinueDataAsset* info = node->GetSGSCppCustomGraphNodeInfo();
                    //info->SGSCppCustomGraphResponses.RemoveAt(info->SGSCppCustomGraphResponses.Num() - 1);

                    if (info->OutputTags.Num() != 0) info->OutputTags.RemoveAt(info->OutputTags.Num() - 1);
                    
                    if (info->OutputTags.Num() == 0) node->CreateDefaultOutputPins();
                    
                    node->SyncPinsWithResponses();

                    node->GetGraph()->NotifyGraphChanged();
                    node->GetGraph()->Modify();
                }
            }
        ))
    );
    */

    section.AddMenuEntry(
        TEXT("DeleteEntry"),
        FText::FromString(TEXT("Delete Node")),
        FText::FromString(TEXT("Deletes the node")),
        FSlateIcon(TEXT("SGSCppCustomGraphAssetEditorStyle"), TEXT("SGSCppCustomGraphAssetEditor.NodeDeleteNodeIcon")),
        FUIAction(FExecuteAction::CreateLambda(
            [node] () {
                node->GetGraph()->RemoveNode(node);
            }
        ))
    );
}

UEdGraphPin* USGSCppCustomGraphAssetEditorNodeContinueDataAsset::CreateSGSCppCustomGraphPin(EEdGraphPinDirection direction, FName name) {
    FName category = (direction == EEdGraphPinDirection::EGPD_Input) ? TEXT("Inputs") : TEXT("Outputs");
    FName subcategory = TEXT("SGSCppCustomGraphPin");

    UEdGraphPin* pin = CreatePin(
        direction,
        category,
        name
    );
    
    pin->PinType.PinSubCategory = subcategory;

    return pin;
}

UEdGraphPin* USGSCppCustomGraphAssetEditorNodeContinueDataAsset::CreateDefaultInputPin() { 
    return CreateSGSCppCustomGraphPin(EEdGraphPinDirection::EGPD_Input, TEXT("InputPin"));
}

void USGSCppCustomGraphAssetEditorNodeContinueDataAsset::CreateDefaultOutputPins() {

    //FString defaultResponse = TEXT("Continue");
    //CreateSGSCppCustomGraphPin(EEdGraphPinDirection::EGPD_Output, FName(defaultResponse));
    
    USGSCppV4_GraphNodeInfoContinueDA* nodeInfoLocal = GetSGSCppCustomGraphNodeInfo();
    
    FGameplayTag MyTagBackLocal = FGameplayTag::RequestGameplayTag(FName("SGSCppGraph.Output.Continue"));
    nodeInfoLocal->OutputTags.Add(MyTagBackLocal);
    
    SyncPinsWithResponses();
}

void USGSCppCustomGraphAssetEditorNodeContinueDataAsset::SyncPinsWithResponses() {
    // Sync the pins on the node with the SGSCppCustomGraph responses
    // We're going to assume the first pin is always the
    // input pin
    USGSCppV4_GraphNodeInfoContinueDA* nodeInfo = GetSGSCppCustomGraphNodeInfo();
    int numGraphNodePins = Pins.Num() - 1;
    //int numInfoPins = nodeInfo->SGSCppCustomGraphResponses.Num();
    int numInfoPins = nodeInfo->OutputTags.Num();


    while (numGraphNodePins > numInfoPins) {
        RemovePinAt(numGraphNodePins - 1, EEdGraphPinDirection::EGPD_Output);
        numGraphNodePins--;
    }
    while (numInfoPins > numGraphNodePins) {
        CreateSGSCppCustomGraphPin(
            EEdGraphPinDirection::EGPD_Output,
            //FName(nodeInfo->SGSCppCustomGraphResponses[numGraphNodePins].ToString())
            FName(nodeInfo->OutputTags[numGraphNodePins].ToString())
        );
        numGraphNodePins++;
    }

    int index = 1;
    for (const FGameplayTag& option : nodeInfo->OutputTags) {

        FString TagName = option.ToString();
        TagName.RemoveFromStart(TEXT("SGSCppGraph.Output."));

        GetPinAt(index)->PinName = FName(*TagName);
        index++;
    }
}
