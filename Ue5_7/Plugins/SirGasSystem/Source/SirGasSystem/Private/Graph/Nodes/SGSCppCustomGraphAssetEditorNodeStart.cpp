// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#include "Graph/Nodes/SGSCppCustomGraphAssetEditorNodeStart.h"

UEdGraphPin* USGSCppCustomGraphAssetEditorNodeStart::CreateSGSCppCustomGraphPin(EEdGraphPinDirection direction, FName name) {
    FName category = TEXT("Outputs");
    FName subcategory = TEXT("StartPin");

    UEdGraphPin* pin = CreatePin(
        EEdGraphPinDirection::EGPD_Output,
        category,
        name
    );
    pin->PinType.PinSubCategory = subcategory;

    return pin;
}
