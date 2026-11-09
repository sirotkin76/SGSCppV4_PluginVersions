// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#include "Graph/SGSCppV4_CustomGraphAsset.h"

#include "DataAssets/SGSCppV4_DataAsset_Attr.h"
#include "Data/SGSCppV4_GraphRuntimeStuctures.h"

#include "Nodes/SGSCppV4_GraphNodeInfoContinue.h"
#include "Nodes/SGSCppV4_GraphNodeInfoContinueCD.h"
#include "Nodes/SGSCppV4_GraphNodeInfoContinueDA.h"
#include "UObject/ObjectSaveContext.h"


void USGSCppV4_CustomGraphAsset::SGSCppFindNode_GetAttrData_00_Pure(int32 UniqueIndexNode, FText& OutTitle, FText& OutDescription, TArray<FGameplayTag>& OutOutputTags, ESGSCppV4_CustomGraphNodeType& OutNodeType)
{
    FOutputData localData;
    localData.UniqueIndexNodeInGraph = -99;
    localData.NodeType = ESGSCppV4_CustomGraphNodeType::ErrorNodeOrNullNode;

    for (int i = 0; i < GetSGSCppGraph()->GetSGSCppNodes().Num(); i++)
    {
        if (GetSGSCppGraph()->GetSGSCppNodes()[i]->NodeInfo != nullptr)
        {
            if (GetSGSCppGraph()->GetSGSCppNodes()[i]->NodeInfo->UniqueIndexNodeInGraph == UniqueIndexNode)
            {
                OutTitle = GetSGSCppGraph()->GetSGSCppNodes()[i]->NodeInfo->Title;
                OutDescription = GetSGSCppGraph()->GetSGSCppNodes()[i]->NodeInfo->Description;
                OutOutputTags = GetSGSCppGraph()->GetSGSCppNodes()[i]->NodeInfo->OutputTags;
                OutNodeType = GetSGSCppGraph()->GetSGSCppNodes()[i]->NodeType;
            }
        }
    }
}

FOutputData USGSCppV4_CustomGraphAsset::SGSCppFindOutputDataUseIndex(int32 UniqueIndexNode)
{
    FOutputData localData;
    localData.UniqueIndexNodeInGraph = -98;
    localData.NodeType = ESGSCppV4_CustomGraphNodeType::ErrorNodeOrNullNode;

    for (int i = 0; i < GetSGSCppGraph()->GetSGSCppNodes().Num(); i++)
    {
        if (GetSGSCppGraph()->GetSGSCppNodes()[i]->NodeInfo != nullptr)
        {
            if (GetSGSCppGraph()->GetSGSCppNodes()[i]->NodeInfo->UniqueIndexNodeInGraph == UniqueIndexNode)
            {
                return GetSGSCppGraph()->GetSGSCppNodes()[i]->GetSGSCppNodeVariables();
            }
        }
    }

    return FOutputData();
}


FOutputData USGSCppV4_CustomGraphAsset::SGSCppFindDataUseNode(USGSCppCustomGraphRuntimePin * SGSCppCustomGraphRuntimePinLocal)
{
    int32 ResFindNode;
    FOutputData localTempData;
    ResFindNode = GetSGSCppGraph()->GetSGSCppNodes().Find(SGSCppCustomGraphRuntimePinLocal->GetSGSCppConnectionNode());

    //if (ResFindNode != -1) return SGSCppFindDataUseIndex(ResFindNode);

    return localTempData;
}

FOutputData USGSCppV4_CustomGraphAsset::SGSCppFindDataUseFindTag(FGameplayTag InInputTag)
{
    FOutputData localTempData;
    
    if (!InInputTag.IsValid()) return localTempData;
    
    TArray<USGSCppCustomGraphRuntimeNode*>  NodesLocal = GetSGSCppGraph()->GetSGSCppNodes();

    for (int i = 0; i < NodesLocal.Num(); i++)
    {
        USGSCppV4_GraphNodeInfo* NodeInfoL = NodesLocal[i]->NodeInfo;
        if (IsValid(NodeInfoL))
        {
            USGSCppV4_GraphNodeInfoContinue* CastNodeContinue = Cast<USGSCppV4_GraphNodeInfoContinue>(NodeInfoL);
			
            if (IsValid(CastNodeContinue))
            {
                if (CastNodeContinue->UniqueTagToSearchForThisNode == InInputTag)
                {
                    return NodesLocal[i]->GetSGSCppNodeVariables();
                }
            }
        }
    }
	
    return localTempData;

}

int32 USGSCppV4_CustomGraphAsset::SGSCppGetUniqueIndexFirstNode()
{
    if (!IsValid(GetSGSCppGraph())) return -1;
    if (!IsValid(GetSGSCppGraph()->GetSGSCppNodes()[0])) return -1;
    if (!IsValid(GetSGSCppGraph()->GetSGSCppNodes()[0]->GetSGSCppOutputPins()[0])) return -1;
    if (!IsValid(GetSGSCppGraph()->GetSGSCppNodes()[0]->GetSGSCppOutputPins()[0]->GetSGSCppConnectionNode())) return -1;
    if (!IsValid(GetSGSCppGraph()->GetSGSCppNodes()[0]->GetSGSCppOutputPins()[0]->GetSGSCppConnectionNode()->GetSGSCppNodeInfo()))
    {
        return GetSGSCppGraph()->GetSGSCppNodes()[0]->GetSGSCppOutputPins()[0]->GetSGSCppConnectionNode()->GetUniqueID(); // USGSCppCustomGraphRuntimePin
    }

    int32 localOutputData = GetSGSCppGraph()->GetSGSCppNodes()[0]->GetSGSCppOutputPins()[0]->GetSGSCppConnectionNode()->GetSGSCppNodeInfo()->UniqueIndexNodeInGraph;
    
    return localOutputData;
}

void USGSCppV4_CustomGraphAsset::SGSCppFindNode_GetAttrData_00_UseTag(int32 UniqueIndexNodeInGraphForFindData,
    FGameplayTag ResponceTag, int32& OutUniqueIndexNodeInGraph, FText& OutTitle, FText& OutDescription, TArray<FGameplayTag>& OutOutputTags, ESGSCppV4_CustomGraphNodeType& OutNodeType)
{
    FOutputData localOutputData;

    if (UniqueIndexNodeInGraphForFindData < 0) return ;
    
    if (!ResponceTag.IsValid()) return ;
    
    FOutputPinDataV2 localOutputPinDataV2 = SGSCppGetOutpinDataUseUniqueIndexNode(UniqueIndexNodeInGraphForFindData);
    
    int32 localFind = localOutputPinDataV2.OutputTags.Find(ResponceTag);

    //UE_LOG(LogTemp, Error, TEXT("OutputTagInNode : %s"), *OutputTagInNode.ToString());
    //UE_LOG(LogTemp, Error, TEXT("OutputTagInNode : %s"), *localOutputPinDataV2.OutputTags[localFind].ToString());
    
    if (localFind != -1)
    {
        if (localOutputPinDataV2.OutputDataVariables.IsValidIndex(localFind) == true)
        {
            localOutputData = localOutputPinDataV2.OutputDataVariables[localFind];

            OutUniqueIndexNodeInGraph = localOutputData.UniqueIndexNodeInGraph;
            OutTitle = localOutputData.Title;
            OutDescription = localOutputData.Description;
            OutNodeType = localOutputData.NodeType;
            OutOutputTags = localOutputData.OutputPinData.OutputTags;
        }
    }
}

FOutputPinDataV2 USGSCppV4_CustomGraphAsset::SGSCppGetOutpinDataUseUniqueIndexNode(int32 UniqueIndexNodeInGraphForFindData)
{
    FOutputPinDataV2 localOutputData;
    TArray<FOutputData> localArrOutputData;

    TArray<USGSCppCustomGraphRuntimePin*> localOutputPins = SGSCppFindDataUseUniqueIndexNode(UniqueIndexNodeInGraphForFindData).OutputPinData.OutputPins;

    for (USGSCppCustomGraphRuntimePin* pin : localOutputPins)
    {
        if (IsValid(pin) && IsValid(pin->Connection) && IsValid(pin->GetSGSCppConnectionNode()) && true)
        {
            localArrOutputData.Add(pin->GetSGSCppConnectionNode()->GetSGSCppNodeVariables());
        }
        else
        {
            FOutputData localTemp;
            localArrOutputData.Add(localTemp);
        }
    }

    localOutputData.OutputDataVariables = localArrOutputData;
    localOutputData.OutputTags = SGSCppFindDataUseUniqueIndexNode(UniqueIndexNodeInGraphForFindData).OutputPinData.OutputTags;
    
    return localOutputData;
}

void USGSCppV4_CustomGraphAsset::SGSCppFindNodeUse_TagForFindNode(FGameplayTag TagForFindNode,
    int32& UniqueIndexNodeInGraphForFindData)
{
    TArray<USGSCppCustomGraphRuntimeNode*>  NodesLocal = GetSGSCppGraph()->GetSGSCppNodes();

    for (int i = 0; i < NodesLocal.Num(); i++)
    {
        USGSCppV4_GraphNodeInfo* NodeInfoL = NodesLocal[i]->NodeInfo;
        if (IsValid(NodeInfoL))
        {
            USGSCppV4_GraphNodeInfoContinue* CastNodeContinue = Cast<USGSCppV4_GraphNodeInfoContinue>(NodeInfoL);
			
            if (IsValid(CastNodeContinue))
            {
                if (CastNodeContinue->UniqueTagToSearchForThisNode == TagForFindNode)
                {
                    UniqueIndexNodeInGraphForFindData = NodesLocal[i]->GetSGSCppNodeVariables().UniqueIndexNodeInGraph;
                    return ;
                }
            }
        }
    }
}

int32 USGSCppV4_CustomGraphAsset::SGSCppFindNodeContinueGetData_01_FindArrInt(int32 UniqueIndexNode, FName FindNameInArr)
{
    FOutputData localOutputData;

    if (UniqueIndexNode < 0) return -2;
    
    localOutputData.NodeType = ESGSCppV4_CustomGraphNodeType::ErrorNodeOrNullNode;
    localOutputData = SGSCppFindOutputDataUseIndex(UniqueIndexNode);
    
    if (localOutputData.NodeType == ESGSCppV4_CustomGraphNodeType::ErrorNodeOrNullNode) return -2;

    USGSCppCustomGraphRuntimeNode* localNode = SGSCppFindNodeUseUniqueIndex(UniqueIndexNode);
    if (localNode == nullptr) return -2;
    
    USGSCppV4_GraphNodeInfoContinueCD* localCustomNode = Cast<USGSCppV4_GraphNodeInfoContinueCD>(localNode->NodeInfo);
    if (IsValid(localCustomNode)) return localCustomNode->SGSCppFindArrInt(FindNameInArr);

    USGSCppV4_GraphNodeInfoContinueDA* localDataAssetNode = Cast<USGSCppV4_GraphNodeInfoContinueDA>(localNode->NodeInfo);
    if (IsValid(localDataAssetNode)) return localOutputData.OutputNodeContinueGetData.NodeContinue_GetSGSCppDataAssetAttrV3->SGSCppFindArrInt(FindNameInArr);
    
    return -2;
}

float USGSCppV4_CustomGraphAsset::SGSCppFindNodeContinueGetData_01_FindArrFloat(int32 UniqueIndexNode, FName FindNameInArr)
{
    FOutputData localOutputData;

    if (UniqueIndexNode < 0) return -2;
    
    localOutputData.NodeType = ESGSCppV4_CustomGraphNodeType::ErrorNodeOrNullNode;
    localOutputData = SGSCppFindOutputDataUseIndex(UniqueIndexNode);
    
    if (localOutputData.NodeType == ESGSCppV4_CustomGraphNodeType::ErrorNodeOrNullNode) return -2;

    USGSCppCustomGraphRuntimeNode* localNode = SGSCppFindNodeUseUniqueIndex(UniqueIndexNode);
    if (localNode == nullptr) return -2;
    
    USGSCppV4_GraphNodeInfoContinueCD* localCustomNode = Cast<USGSCppV4_GraphNodeInfoContinueCD>(localNode->NodeInfo);
    if (IsValid(localCustomNode)) return localCustomNode->SGSCppFindArrFloat(FindNameInArr);

    USGSCppV4_GraphNodeInfoContinueDA* localDataAssetNode = Cast<USGSCppV4_GraphNodeInfoContinueDA>(localNode->NodeInfo);
    if (IsValid(localDataAssetNode)) return localOutputData.OutputNodeContinueGetData.NodeContinue_GetSGSCppDataAssetAttrV3->SGSCppFindArrFloat(FindNameInArr);
    
    return -2;
}

FText USGSCppV4_CustomGraphAsset::SGSCppFindNodeContinueGetData_01_FindArrText(int32 UniqueIndexNode, FName FindNameInArr)
{
    FOutputData localOutputData;
    FText ErrorMessage = FText::FromString(TEXT("Error"));

    if (UniqueIndexNode < 0) return ErrorMessage;
    
    localOutputData.NodeType = ESGSCppV4_CustomGraphNodeType::ErrorNodeOrNullNode;
    localOutputData = SGSCppFindOutputDataUseIndex(UniqueIndexNode);
    
    if (localOutputData.NodeType == ESGSCppV4_CustomGraphNodeType::ErrorNodeOrNullNode) return  ErrorMessage;

    USGSCppCustomGraphRuntimeNode* localNode = SGSCppFindNodeUseUniqueIndex(UniqueIndexNode);
    if (localNode == nullptr) return  ErrorMessage;
    
    USGSCppV4_GraphNodeInfoContinueCD* localCustomNode = Cast<USGSCppV4_GraphNodeInfoContinueCD>(localNode->NodeInfo);
    if (IsValid(localCustomNode)) return localCustomNode->SGSCppFindArrText(FindNameInArr);

    USGSCppV4_GraphNodeInfoContinueDA* localDataAssetNode = Cast<USGSCppV4_GraphNodeInfoContinueDA>(localNode->NodeInfo);
    if (IsValid(localDataAssetNode)) return localOutputData.OutputNodeContinueGetData.NodeContinue_GetSGSCppDataAssetAttrV3->SGSCppFindArrText(FindNameInArr);
    
    return  ErrorMessage;
}

FName USGSCppV4_CustomGraphAsset::SGSCppFindNodeContinueGetData_01_FindArrName(int32 UniqueIndexNode, FName FindNameInArr)
{
    FOutputData localOutputData;
    FName ErrorMessage = "Error";
    
    if (UniqueIndexNode < 0) return ErrorMessage;
    
    localOutputData.NodeType = ESGSCppV4_CustomGraphNodeType::ErrorNodeOrNullNode;
    
    localOutputData = SGSCppFindOutputDataUseIndex(UniqueIndexNode);
    
    if (localOutputData.NodeType == ESGSCppV4_CustomGraphNodeType::ErrorNodeOrNullNode) return  ErrorMessage;

    USGSCppCustomGraphRuntimeNode* localNode = SGSCppFindNodeUseUniqueIndex(UniqueIndexNode);
    if (localNode == nullptr) return  ErrorMessage;
    
    USGSCppV4_GraphNodeInfoContinueCD* localCustomNode = Cast<USGSCppV4_GraphNodeInfoContinueCD>(localNode->NodeInfo);
    if (IsValid(localCustomNode)) return localCustomNode->SGSCppFindArrName(FindNameInArr);

    USGSCppV4_GraphNodeInfoContinueDA* localDataAssetNode = Cast<USGSCppV4_GraphNodeInfoContinueDA>(localNode->NodeInfo);
    if (IsValid(localDataAssetNode)) return localOutputData.OutputNodeContinueGetData.NodeContinue_GetSGSCppDataAssetAttrV3->SGSCppFindArrName(FindNameInArr);
    
    return  ErrorMessage;
}

FGameplayTagContainer USGSCppV4_CustomGraphAsset::SGSCppFindNodeContinueGetData_01_FindArrGameplayTags(
    int32 UniqueIndexNode, FName FindNameInArr)
{
    FOutputData localOutputData;
    FGameplayTagContainer ErrorMessage;
    
    if (UniqueIndexNode < 0) return ErrorMessage;
    
    localOutputData.NodeType = ESGSCppV4_CustomGraphNodeType::ErrorNodeOrNullNode;
    localOutputData = SGSCppFindOutputDataUseIndex(UniqueIndexNode);
    
    if (localOutputData.NodeType == ESGSCppV4_CustomGraphNodeType::ErrorNodeOrNullNode) return ErrorMessage;

    USGSCppCustomGraphRuntimeNode* localNode = SGSCppFindNodeUseUniqueIndex(UniqueIndexNode);
    if (localNode == nullptr) return ErrorMessage;
    
    USGSCppV4_GraphNodeInfoContinueCD* localCustomNode = Cast<USGSCppV4_GraphNodeInfoContinueCD>(localNode->NodeInfo);
    if (IsValid(localCustomNode)) return localCustomNode->SGSCppFindArrGameplayTags(FindNameInArr);

    USGSCppV4_GraphNodeInfoContinueDA* localDataAssetNode = Cast<USGSCppV4_GraphNodeInfoContinueDA>(localNode->NodeInfo);
    if (IsValid(localDataAssetNode)) return localOutputData.OutputNodeContinueGetData.NodeContinue_GetSGSCppDataAssetAttrV3->SGSCppFindArrGameplayTags(FindNameInArr);
    
    return ErrorMessage;
}

TSoftObjectPtr<UObject> USGSCppV4_CustomGraphAsset::SGSCppFindNodeContinueGetData_01_FindArrUObject(int32 UniqueIndexNode,
                                                                                                 FName FindNameInArr)
{
    FOutputData localOutputData;
    USGSCppCustomGraphRuntimeNode* ErrorMessage = nullptr;
    
    if (UniqueIndexNode < 0) return ErrorMessage;
    
    localOutputData.NodeType = ESGSCppV4_CustomGraphNodeType::ErrorNodeOrNullNode;
    localOutputData = SGSCppFindOutputDataUseIndex(UniqueIndexNode);
    
    if (localOutputData.NodeType == ESGSCppV4_CustomGraphNodeType::ErrorNodeOrNullNode) return ErrorMessage;

    USGSCppCustomGraphRuntimeNode* localNode = SGSCppFindNodeUseUniqueIndex(UniqueIndexNode);
    if (localNode == nullptr) return ErrorMessage;
    
    USGSCppV4_GraphNodeInfoContinueCD* localCustomNode = Cast<USGSCppV4_GraphNodeInfoContinueCD>(localNode->NodeInfo);
    if (IsValid(localCustomNode)) return localCustomNode->SGSCppFindArrUObject(FindNameInArr);

    USGSCppV4_GraphNodeInfoContinueDA* localDataAssetNode = Cast<USGSCppV4_GraphNodeInfoContinueDA>(localNode->NodeInfo);
    if (IsValid(localDataAssetNode)) return localOutputData.OutputNodeContinueGetData.NodeContinue_GetSGSCppDataAssetAttrV3->SGSCppFindArrUObject(FindNameInArr);
    
    return ErrorMessage;
}

TSubclassOf<UObject> USGSCppV4_CustomGraphAsset::SGSCppFindNodeContinueGetData_01_FindArrClassUObject(
    int32 UniqueIndexNode, FName FindNameInArr)
{
    FOutputData localOutputData;
    TSubclassOf<UObject> ErrorMessage = nullptr;
    
    if (UniqueIndexNode < 0) return ErrorMessage;
    
    localOutputData.NodeType = ESGSCppV4_CustomGraphNodeType::ErrorNodeOrNullNode;
    localOutputData = SGSCppFindOutputDataUseIndex(UniqueIndexNode);
    
    if (localOutputData.NodeType == ESGSCppV4_CustomGraphNodeType::ErrorNodeOrNullNode) return ErrorMessage;
    
    USGSCppCustomGraphRuntimeNode* localNode = SGSCppFindNodeUseUniqueIndex(UniqueIndexNode);
    if (localNode == nullptr) return ErrorMessage;
    
    USGSCppV4_GraphNodeInfoContinueCD* localCustomNode = Cast<USGSCppV4_GraphNodeInfoContinueCD>(localNode->NodeInfo);
    if (IsValid(localCustomNode)) return localCustomNode->SGSCppFindArrClassUObject(FindNameInArr);
    
    USGSCppV4_GraphNodeInfoContinueDA* localDataAssetNode = Cast<USGSCppV4_GraphNodeInfoContinueDA>(localNode->NodeInfo);
    if (IsValid(localDataAssetNode)) return localDataAssetNode->GetSGSCppCastSGSCppDataAssetAttrV3()->SGSCppFindArrClassUObject(FindNameInArr);
    
    return ErrorMessage;
}

void USGSCppV4_CustomGraphAsset::SGSCppFindNode_ContinueDataAsset_GetAttrData_01(int32 UniqueIndexNodeInGraphForFindData,
    USGSCppV4_DataAsset_Attr*& SGSCppDataAssetAttrV3, UPrimaryDataAsset*& PrimaryDataAsset)
{
    FOutputData localOutputData;
    FGameplayTagContainer ErrorMessage;
    
    if (UniqueIndexNodeInGraphForFindData < 0) return ;
    
    localOutputData.NodeType = ESGSCppV4_CustomGraphNodeType::ErrorNodeOrNullNode;
    localOutputData = SGSCppFindOutputDataUseIndex(UniqueIndexNodeInGraphForFindData);
    
    if (localOutputData.NodeType == ESGSCppV4_CustomGraphNodeType::ErrorNodeOrNullNode) return ;

    USGSCppCustomGraphRuntimeNode* localNode = SGSCppFindNodeUseUniqueIndex(UniqueIndexNodeInGraphForFindData);
    if (localNode == nullptr) return ;

    USGSCppV4_GraphNodeInfoContinueDA* localDataAssetNode = Cast<USGSCppV4_GraphNodeInfoContinueDA>(localNode->NodeInfo);
    if (IsValid(localDataAssetNode))
    {
        SGSCppDataAssetAttrV3 = localDataAssetNode->GetSGSCppCastSGSCppDataAssetAttrV3();
        PrimaryDataAsset = localDataAssetNode->GetSGSCppCastPrimaryDataAsset();
    };
    
    return ;

    
}

void USGSCppV4_CustomGraphAsset::SGSCppFindNode_GetAttrData_00(int32 UniqueIndexNodeInGraphForFindData, FText& Title, FText& Description, TArray<FGameplayTag>& OutputTags, ESGSCppV4_CustomGraphNodeType& NodeType  )
{
    FOutputData localOutputData = SGSCppFindOutputDataUseIndex(UniqueIndexNodeInGraphForFindData);
    
    if (localOutputData.UniqueIndexNodeInGraph < 0) return ;
    
    if (localOutputData.NodeType != ESGSCppV4_CustomGraphNodeType::ErrorNodeOrNullNode)
    {
        Title = localOutputData.Title;
        Description = localOutputData.Description;
        OutputTags = localOutputData.OutputPinData.OutputTags;
        NodeType = localOutputData.NodeType;
    }
}

void USGSCppV4_CustomGraphAsset::SGSCppFindNode_END_GetAttrData_01(int32 UniqueIndexNodeInGraphForFindData,
    FGameplayTag& TagForFindNode, FString& CustomAction, UPrimaryDataAsset*& PrimaryDataAsset)
{
    FOutputData localOutputData = SGSCppFindDataUseUniqueIndexNode(UniqueIndexNodeInGraphForFindData);
    
    TagForFindNode      = localOutputData.EndNodeOnly_TagForFindNode;
    CustomAction        = localOutputData.EndNodeOnly_CustomAction;
    PrimaryDataAsset    = localOutputData.EndNodeOnly_PrimaryDataAsset;
}


USGSCppCustomGraphRuntimeNode* USGSCppV4_CustomGraphAsset::SGSCppFindNodeUseUniqueIndex(int32 UniqueIndexNode)
{
    if (!IsValid(GetSGSCppGraph())) return nullptr;
    
    TArray<USGSCppCustomGraphRuntimeNode*>  NodesLocal = GetSGSCppGraph()->GetSGSCppNodes();
    USGSCppCustomGraphRuntimeNode* localTempData = nullptr; 

    for (int i = 0; i < NodesLocal.Num(); i++)
    {
        USGSCppV4_GraphNodeInfo* NodeInfoL = NodesLocal[i]->NodeInfo;
        if (IsValid(NodeInfoL))
        {
            if (NodeInfoL->UniqueIndexNodeInGraph == UniqueIndexNode) return NodesLocal[i];
        }
    }
	
    return localTempData;

}

FOutputData USGSCppV4_CustomGraphAsset::SGSCppFindDataUseUniqueIndexNode(int32 UniqueIndexNodeInGraphForFindData)
{
    FOutputData localOutputData;
    if (!IsValid(GetSGSCppGraph())) return localOutputData;
    
    for (USGSCppCustomGraphRuntimeNode* runtimeNode : GetSGSCppGraph()->GetSGSCppNodes())
    {
        if (runtimeNode->GetSGSCppNodeVariables().UniqueIndexNodeInGraph == UniqueIndexNodeInGraphForFindData)
        {
            return runtimeNode->GetSGSCppNodeVariables();
        }
    }
    
    return localOutputData;
};

TArray<USGSCppCustomGraphRuntimePin*> USGSCppV4_CustomGraphAsset::GetSGSCppOutputConnectionPins(int32 NodeIndex)
{
    TArray<USGSCppCustomGraphRuntimePin*>  error;
    if (!IsValid(GetSGSCppGraph())) return error;
    
    return GetSGSCppGraph()->GetSGSCppGetNodeInArr(NodeIndex)->GetSGSCppOutputPins();
};

void USGSCppV4_CustomGraphAsset::PreSave(FObjectPreSaveContext saveContext) { 
    if (_onPreSaveListener) {
        _onPreSaveListener();
    }
}
