// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#include "Graph/SGSCppV4_CustomGraphRuntimeGraph.h"

#include "Data/SGSCppV4_GraphRuntimeStuctures.h"
#include "Nodes/USGSCppV4_CustomGraphRuntimeInfoNodeEnd.h"

#include "Nodes/SGSCppV4_GraphNodeInfoContinue.h"
#include "Nodes/SGSCppV4_GraphNodeInfoContinueCD.h"
#include "Nodes/SGSCppV4_GraphNodeInfoContinueDA.h"

USGSCppV4_DataAsset_Attr* USGSCppCustomGraphRuntimeNode::CheckNodeAndGetSGSCppDataAssetAttrV3(USGSCppV4_GraphNodeInfo* NodeInfoLocal)
{
	if (IsValid(NodeInfoLocal))
	{
		USGSCppV4_GraphNodeInfoContinueDA * nodeContinueLocal = Cast<USGSCppV4_GraphNodeInfoContinueDA>(NodeInfoLocal);
		if (IsValid(nodeContinueLocal))
		{
			if (nodeContinueLocal->GetSGSCppCastSGSCppDataAssetAttrV3() != nullptr)
			{
				return nodeContinueLocal->GetSGSCppCastSGSCppDataAssetAttrV3();
			}
		}
	};
	return nullptr;
}


FOutputData USGSCppCustomGraphRuntimeNode::GetSGSCppNodeVariables()
{
	FOutputData PlayerOutputPinDataLocal;

	PlayerOutputPinDataLocal.InputPin = GetSGSCppInputPin();
	PlayerOutputPinDataLocal.NodeType = GetSGSCppNodeType();
	
	PlayerOutputPinDataLocal.OutputPinData.OutputPins = GetSGSCppOutputPins();
	if (IsValid(GetSGSCppNodeInfo()))
	{
		PlayerOutputPinDataLocal.Title = GetSGSCppNodeInfo()->Title;
		PlayerOutputPinDataLocal.Description = GetSGSCppNodeInfo()->Description;
		PlayerOutputPinDataLocal.OutputPinData.OutputTags = GetSGSCppNodeInfo()->OutputTags;
		PlayerOutputPinDataLocal.UniqueIndexNodeInGraph = GetSGSCppNodeInfo()->UniqueIndexNodeInGraph;
	}
	
	USGSCppV4_GraphNodeInfoContinueCD* localCustomData = Cast<USGSCppV4_GraphNodeInfoContinueCD>(NodeInfo);
	if (IsValid(localCustomData))
	{
		PlayerOutputPinDataLocal.OutputNodeContinueGetData.NodeContinueCustomData_GetData = localCustomData;
	}
	
	PlayerOutputPinDataLocal.OutputNodeContinueGetData.NodeContinue_GetSGSCppDataAssetAttrV3 = GetSGSCppCastSGSCppDataAssetAttrV3();
	
	USGSCppV4_CustomGraphRuntimeInfoNodeEnd * CheckNodeLocal = Cast<USGSCppV4_CustomGraphRuntimeInfoNodeEnd>(GetSGSCppNodeInfo());
	if (IsValid(CheckNodeLocal))
	{
		PlayerOutputPinDataLocal.EndNodeOnly_TagForFindNode		= CheckNodeLocal->TagForFindNode;
		PlayerOutputPinDataLocal.EndNodeOnly_CustomAction		= CheckNodeLocal->CustomAction;
		PlayerOutputPinDataLocal.EndNodeOnly_PrimaryDataAsset	= CheckNodeLocal->SGSCppGetCustomDataAsset();
	}

	return PlayerOutputPinDataLocal;
}

USGSCppV4_DataAsset_Attr* USGSCppCustomGraphRuntimeNode::GetSGSCppCastSGSCppDataAssetAttrV3()
{
	return CheckNodeAndGetSGSCppDataAssetAttrV3(NodeInfo);
}

USGSCppCustomGraphRuntimeNode* USGSCppCustomGraphRuntimeNode::GetSGSCppNextOutputNodeByPinIndex(int OutputPinIndex)
{
	if (!OutputPins.IsValidIndex(OutputPinIndex))
	{
		return nullptr;
	}

	USGSCppCustomGraphRuntimePin* OutputPin = OutputPins[OutputPinIndex];
	if (!IsValid(OutputPin))
	{
		return nullptr;
	}

	if (OutputPin->Connection == nullptr)
	{
		return nullptr;
	}

	return OutputPin->Connection->Parent;
}

USGSCppCustomGraphRuntimeNode* USGSCppCustomGraphRuntimeNode::GetSGSCppCheckTagAndGetParentNode(FGameplayTag InInputTag)
{
	FString TagNameLocal = InInputTag.ToString();
	TagNameLocal.RemoveFromStart(TEXT("SGSCppGraph.Output."));

	FName TagNameLocal2 = FName(*TagNameLocal);

	for (int i = 0; i < OutputPins.Num(); i++)
	{
		if (OutputPins[i]->PinName == TagNameLocal2)
		{
			if (IsValid(OutputPins[i]->Connection) && (IsValid(OutputPins[i]->Connection->Parent))) return OutputPins[i]->Connection->Parent;
			else return nullptr;
		}
	}

	return nullptr;
}

/*
USGSCppCustomGraphRuntimeNode* USGSCppV4_CustomGraphRuntimeGraph::GetSGSCppFindNodeUseDataAsset(FPrimaryAssetId PrimaryAssetId)
{
	if (!PrimaryAssetId.IsValid()) return nullptr;
	
	for (int i = 0; i < Nodes.Num(); i++) {
		USGSCppCustomGraphNode* NodeInfoL =  Nodes[i]->NodeInfo;
		if (IsValid(NodeInfoL)) {
			
			UPrimaryDataAsset * DataAssetLocal = CheckNodeAndGetSGSCppDataAssetAttrV3(NodeInfoL);
			
			if (DataAssetLocal != nullptr) {
				if (DataAssetLocal == PrimaryAssetId) {
					return Nodes[i];
				}
			}
		}
	}

	return nullptr;
}
*/

USGSCppCustomGraphRuntimeNode* USGSCppV4_CustomGraphRuntimeGraph::GetSGSCppFindNodeUseTag(FGameplayTag InInputTag)
{
	if (!InInputTag.IsValid()) return nullptr;

	for (int i = 0; i < Nodes.Num(); i++)
	{
		USGSCppV4_GraphNodeInfo* NodeInfoL = Nodes[i]->NodeInfo;
		if (IsValid(NodeInfoL))
		{
			USGSCppV4_GraphNodeInfoContinue* CastNodeContinue = Cast<USGSCppV4_GraphNodeInfoContinue>(NodeInfoL);
			
			if (IsValid(CastNodeContinue))
			{
				if (CastNodeContinue->UniqueTagToSearchForThisNode == InInputTag) return Nodes[i];
			}
		}
	}
	
	return nullptr;
}
