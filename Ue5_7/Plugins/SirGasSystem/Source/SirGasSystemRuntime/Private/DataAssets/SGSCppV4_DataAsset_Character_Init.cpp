// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.


#include "DataAssets/SGSCppV4_DataAsset_Character_Init.h"


UAnimMontage * USGSCppV4_DataAsset_Attr_Character_Init::SGSCppFindArrAnimMontage(FName FindNameInArr)
{
	// Use the Find() function
	if (arrOthers.IsEmpty())		return nullptr;
	if (arrOthers.Num() == 0)		return nullptr;
	if (!FindNameInArr.IsValid())	return nullptr;

	UAnimMontage ** FoundValuePtr;
	FoundValuePtr = arrOthers.Find(FindNameInArr);
	
	if (FoundValuePtr != nullptr) 
	{
		return *FoundValuePtr;
	}

	return nullptr;
}
