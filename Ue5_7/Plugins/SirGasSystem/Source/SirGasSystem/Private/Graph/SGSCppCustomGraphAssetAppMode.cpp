// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#include "Graph/SGSCppCustomGraphAssetAppMode.h"
#include "Graph/SGSCppCustomGraphAssetEditorApp.h"
#include "Graph/SGSCppCustomGraphAssetPrimaryTabFactory.h"
#include "Graph/SGSCppCustomGraphAssetPropertiesTabFactory.h"

SGSCppCustomGraphAssetAppMode::SGSCppCustomGraphAssetAppMode(TSharedPtr<SGSCppCustomGraphAssetEditorApp> app) : FApplicationMode(TEXT("SGSCppCustomGraphAssetAppMode")) {
    _app = app;
    _tabs.RegisterFactory(MakeShareable(new SGSCppCustomGraphAssetPrimaryTabFactory(app)));
    _tabs.RegisterFactory(MakeShareable(new SGSCppCustomGraphAssetPropertiesTabFactory(app)));

    TabLayout = FTabManager::NewLayout("SGSCppCustomGraphAssetAppMode_Layout_v1")
	->AddArea
	(
		FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewSplitter()
					->SetOrientation(Orient_Horizontal)
					->Split
					(
						FTabManager::NewStack()
							->SetSizeCoefficient(0.75)
							->AddTab(FName(TEXT("SGSCppCustomGraphAssetPrimaryTab")), ETabState::OpenedTab)
					)
					->Split
					(
						FTabManager::NewStack()
							->SetSizeCoefficient(0.25)
							->AddTab(FName(TEXT("SGSCppCustomGraphAssetPropertiesTab")), ETabState::OpenedTab)
					)
			)
	);
}

void SGSCppCustomGraphAssetAppMode::RegisterTabFactories(TSharedPtr<class FTabManager> InTabManager) {
    TSharedPtr<SGSCppCustomGraphAssetEditorApp> app = _app.Pin();
	app->PushTabFactories(_tabs);
	FApplicationMode::RegisterTabFactories(InTabManager);
}

void SGSCppCustomGraphAssetAppMode::PreDeactivateMode() {
	FApplicationMode::PreDeactivateMode();
}

void SGSCppCustomGraphAssetAppMode::PostActivateMode() {
	FApplicationMode::PostActivateMode();
}
