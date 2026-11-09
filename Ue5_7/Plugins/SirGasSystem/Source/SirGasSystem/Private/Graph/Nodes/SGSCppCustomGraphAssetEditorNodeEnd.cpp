// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#include "Graph/Nodes/SGSCppCustomGraphAssetEditorNodeEnd.h"

#include "GameplayTagContainer.h"

FText USGSCppCustomGraphAssetEditorNodeEnd::GetNodeTitle(ENodeTitleType::Type titalType) const {

    FText localTitle = FText::FromString(TEXT("Node End"));

    if (!_nodeInfo->Title.IsEmpty()) return _nodeInfo->Title;
    if (_nodeInfo->TagForFindNode.IsValid()) return FText::FromString(TEXT("Node End - Find Tag"));
    
    return localTitle;
    
    /*
    if (_nodeInfo != nullptr && _nodeInfo->Action != ESGSCppCustomGraphNodeAction::None) {
        FString result = UEnum::GetDisplayValueAsText(_nodeInfo->Action).ToString();
        if (!_nodeInfo->ActionData.IsEmpty()) {
            FString actionData = _nodeInfo->ActionData;
            if (actionData.Len() > 15) {
                actionData = actionData.Left(15) + TEXT("...");
            }
            result += TEXT(" - ") + actionData;
        }
        return FText::FromString(result);
    }
  

    return FText::FromString(TEXT("End"));  */
}

void USGSCppCustomGraphAssetEditorNodeEnd::GetNodeContextMenuActions(class UToolMenu* menu, class UGraphNodeContextMenuContext* context) const {
    FToolMenuSection& section = menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("End Node Actions")));

    USGSCppCustomGraphAssetEditorNodeEnd* node = (USGSCppCustomGraphAssetEditorNodeEnd*)this;
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

UEdGraphPin* USGSCppCustomGraphAssetEditorNodeEnd::CreateSGSCppCustomGraphPin(EEdGraphPinDirection direction, FName name) {
    FName category = TEXT("Inputs");
    FName subcategory = TEXT("EndPin");

    UEdGraphPin* pin = CreatePin(
        direction,
        category,
        name
    );
    pin->PinType.PinSubCategory = subcategory;

    return pin;
}

UEdGraphPin* USGSCppCustomGraphAssetEditorNodeEnd::CreateDefaultInputPin() { 
    return CreateSGSCppCustomGraphPin(EEdGraphPinDirection::EGPD_Input, FName(TEXT("Finish")));
}
