// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#include "DataAssets/SGSCppV4_DataAsset_Attr.h"


USGSCppV4_DataAsset_Attr::USGSCppV4_DataAsset_Attr()
{
}

bool USGSCppV4_DataAsset_Attr::SGSCppFindArrBool(FName FindNameInArr)
{
    // Use the Find() function
    if (ArrInt32.IsEmpty())			return false;
    if (ArrInt32.Num() == 0)		return false;
    if (!FindNameInArr.IsValid())	return false;
    
    bool * FoundValuePtr = ArrBool.Find(FindNameInArr);

    if (FoundValuePtr != nullptr)
    {
        return *FoundValuePtr;

    }
    else return false;
}

int32 USGSCppV4_DataAsset_Attr::SGSCppFindArrInt(FName FindNameInArr)
{
    // Use the Find() function
    if (ArrInt32.IsEmpty())			return -1;
    if (ArrInt32.Num() == 0)		return -1;
    if (!FindNameInArr.IsValid())	return -1;
    
    int32 * FoundValuePtr = ArrInt32.Find(FindNameInArr);

    if (FoundValuePtr != nullptr)
    {
        return *FoundValuePtr;

    }
    else return -1;
}

float USGSCppV4_DataAsset_Attr::SGSCppFindArrFloat(FName FindNameInArr)
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

FText USGSCppV4_DataAsset_Attr::SGSCppFindArrText(FName FindNameInArr)
{
    // Use the Find() function
    if (ArrText.IsEmpty())			return FText();
    if (ArrText.Num() == 0)			return FText();
    if (!FindNameInArr.IsValid())	return FText();
    
    FText * FoundValuePtr = ArrText.Find(FindNameInArr);

    if (FoundValuePtr != nullptr)
    {
        return *FoundValuePtr;

    }
    return FText();
}

FName USGSCppV4_DataAsset_Attr::SGSCppFindArrName(FName FindNameInArr)
{
    // Use the Find() function
    if (ArrName.IsEmpty())			return FName();
    if (ArrName.Num() == 0)			return FName();
    if (!FindNameInArr.IsValid())	return FName();
    
    FName* FoundValuePtr = ArrName.Find(FindNameInArr);

    if (FoundValuePtr != nullptr)
    {
        return *FoundValuePtr;
    }

    return FName();
}

FString USGSCppV4_DataAsset_Attr::SGSCppFindArrString(FName FindNameInArr)
{
    // Use the Find() function
    if (ArrName.IsEmpty())			return FString("");
    if (ArrName.Num() == 0)			return FString("");
    if (!FindNameInArr.IsValid())	return FString("");
    
    FString * FoundValuePtr = ArrString.Find(FindNameInArr);

    if (FoundValuePtr != nullptr)
    {
        return *FoundValuePtr;
    }

    return FString("");
}

TSoftObjectPtr<UObject> USGSCppV4_DataAsset_Attr::SGSCppFindArrUObject(FName FindNameInArr)
{
    // Use the Find() function
    if (ArrUObject.IsEmpty())		return nullptr;
    if (ArrUObject.Num() == 0)		return nullptr;
    if (!FindNameInArr.IsValid())	return nullptr;

    TSoftObjectPtr<UObject> * FoundValuePtr = ArrUObject.Find(FindNameInArr);
    if (FoundValuePtr != nullptr) 
    {
        TSoftObjectPtr<UObject> MyGenericAsset = *FoundValuePtr;
        return MyGenericAsset;
    }

    return nullptr;
}

TSubclassOf<UObject> USGSCppV4_DataAsset_Attr::SGSCppFindArrClassUObject(FName FindNameInArr)
{
    if (ArrClassUObject.IsEmpty())		return TSubclassOf<UObject>();
    if (ArrClassUObject.Num() == 0)		return TSubclassOf<UObject>();
    if (!FindNameInArr.IsValid())		return TSubclassOf<UObject>();

    TSubclassOf<UObject> * FoundValuePtr = ArrClassUObject.Find(FindNameInArr);
    if (FoundValuePtr != nullptr)
    {
        TSubclassOf<UObject> MyGenericAsset = *FoundValuePtr;
        return MyGenericAsset;
    }

    return TSubclassOf<UObject>();
}

FGameplayTagContainer USGSCppV4_DataAsset_Attr::SGSCppFindArrGameplayTags(FName FindNameInArr)
{
    FGameplayTagContainer * LocalData;
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
}
