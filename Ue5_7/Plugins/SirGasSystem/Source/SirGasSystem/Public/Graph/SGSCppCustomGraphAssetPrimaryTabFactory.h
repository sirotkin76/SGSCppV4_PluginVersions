// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"

class SGSCppCustomGraphAssetPrimaryTabFactory : public FWorkflowTabFactory {
public:
	SGSCppCustomGraphAssetPrimaryTabFactory(TSharedPtr<class SGSCppCustomGraphAssetEditorApp> app);

	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;

protected:
	TWeakPtr<class SGSCppCustomGraphAssetEditorApp> _app;
};
