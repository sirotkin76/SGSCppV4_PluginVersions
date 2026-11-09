// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "GameplayTagContainer.h"
#include "Nodes/SGSCppV4_CustomGraphNodeType.h"
#include "Engine/DataAsset.h"
#include "DataAssets/SGSCppV4_DataAsset_Attr.h"

#include "SGSCppV4_GraphRuntimeStuctures.generated.h"

struct FOutputData;

class USGSCppCustomGraphRuntimePin;
class USGSCppV4_GraphNodeInfoContinueCD;



USTRUCT(BlueprintType)
struct FOutputNodeContinue
{
	GENERATED_BODY()
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	USGSCppV4_DataAsset_Attr* NodeContinue_GetSGSCppDataAssetAttrV3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	USGSCppV4_GraphNodeInfoContinueCD* NodeContinueCustomData_GetData;

};

USTRUCT(BlueprintType)
struct FOutputPinData
{
	GENERATED_BODY()
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<FGameplayTag> OutputTags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<USGSCppCustomGraphRuntimePin*> OutputPins;

};

USTRUCT(BlueprintType)
struct FOutputData
{
	GENERATED_BODY()
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 UniqueIndexNodeInGraph;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	USGSCppCustomGraphRuntimePin* InputPin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	ESGSCppV4_CustomGraphNodeType NodeType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|NodeContinue")
	FOutputNodeContinue OutputNodeContinueGetData;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|NodeContinue")
	FOutputPinData OutputPinData;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|NodeEnd")
	FGameplayTag EndNodeOnly_TagForFindNode;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|NodeEnd")
	FString EndNodeOnly_CustomAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data|NodeEnd")
	UPrimaryDataAsset* EndNodeOnly_PrimaryDataAsset;
    
};


USTRUCT(BlueprintType)
struct FOutputPinDataV2
{
	GENERATED_BODY()
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<FGameplayTag> OutputTags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<FOutputData> OutputDataVariables;
};

