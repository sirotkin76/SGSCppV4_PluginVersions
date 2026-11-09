// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#include "Nodes/USGSCppV4_CustomGraphRuntimeInfoNodeEnd.h"

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"

UPrimaryDataAsset* USGSCppV4_CustomGraphRuntimeInfoNodeEnd::SGSCppGetCustomDataAsset()
{
    FPrimaryAssetId AssetId = CustomDataAsset;
    UAssetManager& Manager = UAssetManager::Get();
    // Get the object from memory
    UObject* LoadedObject = Manager.GetPrimaryAssetObject(AssetId);

    // Cast to your specific Data Asset class
    UPrimaryDataAsset* MyAsset = Cast<UPrimaryDataAsset>(LoadedObject);

    if (MyAsset)
    {
        return MyAsset;
    }
    else
    {
        FSoftObjectPath ItemPath = UAssetManager::Get().GetPrimaryAssetPath(AssetId);


        //FSoftObjectPath SoftLoadedObject = Manager.GetPrimaryAssetObject(AssetId);

        UPrimaryDataAsset* MyAssetLocal = Cast<UPrimaryDataAsset>(ItemPath.TryLoad());

        //UE_LOG(LogTemp, Warning, TEXT("USGSCppDataAssetAttrV3 is loaded"));

        return MyAssetLocal;
        //LoadedObject = Manager.LoadPrimaryAsset(AssetId, TArray<FName>(), FStreamableDelegate::CreateUObject(this, &ThisClass::OnAssetLoaded);
    }
}
