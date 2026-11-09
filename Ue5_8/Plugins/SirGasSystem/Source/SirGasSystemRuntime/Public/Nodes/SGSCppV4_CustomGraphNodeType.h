// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "SGSCppV4_CustomGraphNodeType.generated.h"

UENUM()
enum class ESGSCppV4_CustomGraphNodeType : uint8 {
    Unknown UMETA(DisplayName = "None"),
	StartNode UMETA(DisplayName = "Start node"),
	SGSCppNodeContinueDataAsset UMETA(DisplayName = "Continue node - data asset"),
	SGSCppCustomGraphNodeCustomData UMETA(DisplayName = "Continue node - custom data"),
	EndNode UMETA(DisplayName = "End node"),
	ErrorNodeOrNullNode  UMETA(DisplayName = "Error node or node null")
};

UENUM(BlueprintType)
enum class ESGSCppCustomGraphNodeAction : uint8 {
	None,
	JumpOnNewNodeUseTag,
	JumpOnNewNodeUseDataAsset,
	Action,
	Activate,
	Success,
	Quest,
	End
};
