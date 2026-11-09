// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#include "Nodes/SGSCppV4_GraphNodeInfo.h"
#include "Engine/AssetManager.h"
#include "GameplayTagContainer.h"
#include "Graph/SGSCppV4_CustomGraphRuntimeGraph.h"

USGSCppCustomGraphRuntimeNode* USGSCppV4_GraphNodeInfo::GetSGSCppOutputNode(FGameplayTag InInputTag, USGSCppCustomGraphRuntimeNode* SGSCppCustomGraphRuntimeNode)
{
    FGameplayTag InputTag;

    for (int i = 0; i < OutputTags.Num(); i++)
    {
        if (InputTag.MatchesTag(OutputTags[i]))
        {
            USGSCppCustomGraphRuntimeNode* NextNode = SGSCppCustomGraphRuntimeNode->GetSGSCppNextOutputNodeByPinIndex(i);

            if (IsValid(NextNode))
            {
                return NextNode;
            }
        }
    }

    return nullptr;
}

void USGSCppV4_GraphNodeInfo::UpdateUniquIndex()
{
        UniqueIndexNodeInGraph = GetUniqueID();
}
