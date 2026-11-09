// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#include "Nodes/SGSCppV4_GraphNodeInfoContinueDA.h"
#include "Engine/AssetManager.h"
#include "DataAssets/SGSCppV4_DataAsset_Attr.h"

FPrimaryAssetId USGSCppV4_GraphNodeInfoContinueDA::GetSGSCppDataAsset()
{
    return SGSCppDataAssetAttrV3;
}

USGSCppV4_DataAsset_Attr* USGSCppV4_GraphNodeInfoContinueDA::GetSGSCppCastSGSCppDataAssetAttrV3()
{
    FPrimaryAssetId AssetId = GetSGSCppDataAsset();

    UAssetManager& Manager = UAssetManager::Get();
    // Get the object from memory
    UObject* LoadedObject = Manager.GetPrimaryAssetObject(AssetId);

    // Cast to your specific Data Asset class
    USGSCppV4_DataAsset_Attr * MyAsset = Cast<USGSCppV4_DataAsset_Attr>(LoadedObject);

    if (MyAsset)
    {
        return MyAsset;
    }
    else
    {
        FSoftObjectPath ItemPath = UAssetManager::Get().GetPrimaryAssetPath(AssetId);
        
        USGSCppV4_DataAsset_Attr * MyAssetLocal = Cast<USGSCppV4_DataAsset_Attr>(ItemPath.TryLoad());
        
        return MyAssetLocal;
    }
}

UPrimaryDataAsset* USGSCppV4_GraphNodeInfoContinueDA::GetSGSCppCastPrimaryDataAsset()
{
    FPrimaryAssetId AssetId = GetSGSCppDataAsset();

    UAssetManager& Manager = UAssetManager::Get();
    UObject* LoadedObject = Manager.GetPrimaryAssetObject(AssetId);

    UPrimaryDataAsset* MyAsset = Cast<UPrimaryDataAsset>(LoadedObject);

    if (MyAsset)
    {
        return MyAsset;
    }
    else
    {
        FSoftObjectPath ItemPath = UAssetManager::Get().GetPrimaryAssetPath(AssetId);

        UPrimaryDataAsset * MyAssetLocal = Cast<UPrimaryDataAsset>(ItemPath.TryLoad());

        return MyAssetLocal;
    }
}
