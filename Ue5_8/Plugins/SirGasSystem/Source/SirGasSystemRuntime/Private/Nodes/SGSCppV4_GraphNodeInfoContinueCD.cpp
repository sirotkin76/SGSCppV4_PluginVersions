// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#include "Nodes/SGSCppV4_GraphNodeInfoContinueCD.h"
#include "Templates/SubclassOf.h"

int32 USGSCppV4_GraphNodeInfoContinueCD::SGSCppFindArrInt(FName FindNameInArr)
{
	int32 localText = -1;
	// Use the Find() function
	if (ArrInt32.IsEmpty())			return localText;
	if (ArrInt32.Num() == 0)		return localText;
	if (!FindNameInArr.IsValid())	return localText;
	
	int32 * FoundValuePtr = ArrInt32.Find(FindNameInArr);

	if (FoundValuePtr != nullptr)
	{
		return *FoundValuePtr;
	}

	return localText;
}

float USGSCppV4_GraphNodeInfoContinueCD::SGSCppFindArrFloat(FName FindNameInArr)
{

	float localText = -1.0f;
	// Use the Find() function
	if (ArrFloat.IsEmpty())			return localText;
	if (ArrFloat.Num() == 0)		return localText;
	if (!FindNameInArr.IsValid())	return localText;

	float* FoundValuePtr = ArrFloat.Find(FindNameInArr);

	if (FoundValuePtr != nullptr)
	{
		return *FoundValuePtr;
	}

	return -1.0f;
}


FText USGSCppV4_GraphNodeInfoContinueCD::SGSCppFindArrText(FName FindNameInArr)
{
	FText localText;
	// Use the Find() function
	if (ArrText.IsEmpty())			return localText;
	if (ArrText.Num() == 0)			return localText;
	
	if (!FindNameInArr.IsValid())	return localText;
	
	FText * FoundValuePtr = ArrText.Find(FindNameInArr);

	if (FoundValuePtr != nullptr)
	{
		return FText(*FoundValuePtr) ;
	}
	
	return localText;
}

FName USGSCppV4_GraphNodeInfoContinueCD::SGSCppFindArrName(FName FindNameInArr)
{
	FName localName;
	// Use the Find() function
	if (ArrName.IsEmpty())			return localName;
	if (ArrName.Num() == 0)			return localName;
	if (!FindNameInArr.IsValid())	return localName;
	
	FName* FoundValuePtr = ArrName.Find(FindNameInArr);

	if (FoundValuePtr != nullptr)
	{
		return *FoundValuePtr;

	}

	return localName;
}

TSoftObjectPtr<UObject> USGSCppV4_GraphNodeInfoContinueCD::SGSCppFindArrUObject(FName FindNameInArr)
{
	TSoftObjectPtr<UObject> local;
	
	// Use the Find() function
	if (ArrUObject.IsEmpty())		return local;
	if (ArrUObject.Num() == 0)		return local;
	if (!FindNameInArr.IsValid())	return local;
	
		
	TSoftObjectPtr<UObject> * FoundValuePtr = ArrUObject.Find(FindNameInArr);
	if (FoundValuePtr != nullptr) 
	{
		TSoftObjectPtr<UObject> MyGenericAsset = *FoundValuePtr;
		return MyGenericAsset;
	}

	/*
	if (FoundValuePtr != nullptr)
	{
		TSoftObjectPtr<UObject> MyGenericAsset = * FoundValuePtr;

		if (MyGenericAsset.IsValid())
		{
			UAsyncLoader::AsyncLoadObject<USomeObject>(* FoundValuePtr, MyGenericAsset);

			UObject* LoadedObject = MyGenericAsset.LoadSynchronous();
			return LoadedObject;

		}
	}
	*/

	return local;
    

}

TSubclassOf<UObject> USGSCppV4_GraphNodeInfoContinueCD::SGSCppFindArrClassUObject(FName FindNameInArr)
{
	TSubclassOf<UObject> localTemp = nullptr ;
	
	if (ArrClassUObject.IsEmpty())
	{
		return localTemp;
	}
	if (ArrClassUObject.Num() == 0)
	{
		return localTemp;
	}
	if (!FindNameInArr.IsValid())
	{
		return localTemp;
	}
	
	TSubclassOf<UObject> * FoundValuePtr = ArrClassUObject.Find(FindNameInArr);
	
	if (IsValid(*FoundValuePtr))
	{
		TSubclassOf<UObject> MyGenericAsset = *FoundValuePtr;
		return MyGenericAsset;
	}
	
	return localTemp;
}

FGameplayTagContainer USGSCppV4_GraphNodeInfoContinueCD::SGSCppFindArrGameplayTags(FName FindNameInArr)
{
	FGameplayTagContainer* LocalData;
	FGameplayTagContainer LocalDataClear;


	if (ArrClassUObject.IsEmpty())		return LocalDataClear;
	if (ArrClassUObject.Num() == 0)		return LocalDataClear;
	if (!FindNameInArr.IsValid())		return LocalDataClear;


	LocalData = ArrGameplayTags.Find(FindNameInArr);
	if (LocalData != nullptr)
	{
		FGameplayTagContainer MyGenericAsset = *LocalData;
		return MyGenericAsset;
	}

	return LocalDataClear;

	//return FGameplayTagContainer();
}
