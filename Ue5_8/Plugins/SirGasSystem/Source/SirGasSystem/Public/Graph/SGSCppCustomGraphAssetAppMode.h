// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "WorkflowOrientedApp/ApplicationMode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

/** Application mode for main behavior tree editing mode */
class SGSCppCustomGraphAssetAppMode : public FApplicationMode
{
public:
	SGSCppCustomGraphAssetAppMode(TSharedPtr<class SGSCppCustomGraphAssetEditorApp> app);

	//virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;
	virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;
	
	virtual void PreDeactivateMode() override;
	virtual void PostActivateMode() override;

protected:
	TWeakPtr<class SGSCppCustomGraphAssetEditorApp> _app;
	FWorkflowAllowedTabSet _tabs;
};
