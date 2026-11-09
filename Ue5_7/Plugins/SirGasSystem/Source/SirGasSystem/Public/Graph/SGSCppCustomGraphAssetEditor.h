// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "Styling/SlateStyle.h"

class FSGSCppCustomGraphAssetEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedPtr<FSlateStyleSet> _styleSet = nullptr;
	TSharedPtr<struct FSGSCppCustomGraphPinFactory> _pinFactory = nullptr;
};
