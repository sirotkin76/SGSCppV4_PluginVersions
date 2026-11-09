// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#include "Graph/SGSCppCustomGraphAssetFactory.h"
#include "Graph/SGSCppV4_CustomGraphAsset.h"

USGSCppCustomGraphAssetFactory::USGSCppCustomGraphAssetFactory(const FObjectInitializer& objectInitializer) : Super(objectInitializer) {
	SupportedClass = USGSCppV4_CustomGraphAsset::StaticClass();
}

UObject* USGSCppCustomGraphAssetFactory::FactoryCreateNew(UClass* uclass, UObject* inParent, FName name, EObjectFlags flags, UObject* context, FFeedbackContext* warn) {
    USGSCppV4_CustomGraphAsset* asset = NewObject<USGSCppV4_CustomGraphAsset>(inParent, name, flags);
	return asset;
}

bool USGSCppCustomGraphAssetFactory::CanCreateNew() const {
    return true;
}
