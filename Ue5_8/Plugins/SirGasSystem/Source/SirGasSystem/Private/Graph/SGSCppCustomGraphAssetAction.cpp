// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#include "Graph/SGSCppCustomGraphAssetAction.h"
#include "Graph/SGSCppV4_CustomGraphAsset.h"
#include "Graph/SGSCppCustomGraphAssetEditorApp.h"

SGSCppCustomGraphAssetAction::SGSCppCustomGraphAssetAction(EAssetTypeCategories::Type category) {
    _assetCategory = category;
}

FText SGSCppCustomGraphAssetAction::GetName() const {
    return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_MySGSCppCustomGraphAsset", "My SGSCppCustomGraph Asset");
}

FColor SGSCppCustomGraphAssetAction::GetTypeColor() const {
    return FColor::Cyan;
}

UClass* SGSCppCustomGraphAssetAction::GetSupportedClass() const {
    return USGSCppV4_CustomGraphAsset::StaticClass();
}

void SGSCppCustomGraphAssetAction::OpenAssetEditor(const TArray<UObject*>& inObjects, TSharedPtr<class IToolkitHost> editWithinLevelEditor) {
    EToolkitMode::Type mode = editWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (UObject* object : inObjects) {
		USGSCppV4_CustomGraphAsset* SGSCppCustomGraphAsset = Cast<USGSCppV4_CustomGraphAsset>(object);
		if (SGSCppCustomGraphAsset != nullptr) {
			TSharedRef<SGSCppCustomGraphAssetEditorApp> editor(new SGSCppCustomGraphAssetEditorApp());
			editor->InitEditor(mode, editWithinLevelEditor, SGSCppCustomGraphAsset);
		}
	}
}

uint32 SGSCppCustomGraphAssetAction::GetCategories() {
    return _assetCategory;
}
