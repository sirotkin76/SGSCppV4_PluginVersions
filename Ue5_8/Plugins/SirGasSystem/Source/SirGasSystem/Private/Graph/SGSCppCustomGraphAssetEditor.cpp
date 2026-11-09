// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#include "Graph/SGSCppCustomGraphAssetEditor.h"
#include "Graph/SGSCppCustomGraphAssetAction.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"
#include "EdGraphUtilities.h"
#include "KismetPins/SGraphPinColor.h"
#include "EdGraph/EdGraphPin.h"


//IMPLEMENT_MODULE(FSGSCppCustomGraphAssetEditorModule, SGSCppCustomGraphAssetEditor)
IMPLEMENT_MODULE(FSGSCppCustomGraphAssetEditorModule, SirGasSystem)

#define LOCTEXT_NAMESPACE "FSGSCppCustomGraphAssetEditorModule"

class SSGSCppCustomGraphGraphPin : public SGraphPin {
public:
	SLATE_BEGIN_ARGS(SSGSCppCustomGraphGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& inArgs, UEdGraphPin* inGraphPinObj) {
		SGraphPin::Construct(SGraphPin::FArguments(), inGraphPinObj);
	}

protected:
	virtual FSlateColor GetPinColor() const override {
		return FSlateColor(FLinearColor(0.2f, 1.0f, 0.2f));
	}
};

class SSGSCppCustomGraphContinueDataGraphPin : public SGraphPin {
public:
	SLATE_BEGIN_ARGS(SSGSCppCustomGraphGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& inArgs, UEdGraphPin* inGraphPinObj) {
		SGraphPin::Construct(SGraphPin::FArguments(), inGraphPinObj);
	}

protected:
	virtual FSlateColor GetPinColor() const override {
		return FSlateColor(FLinearColor(0.2f, 0.0f, 0.35f));
	}
};


class SSGSCppCustomGraphStartGraphPin : public SGraphPin {
public:
	SLATE_BEGIN_ARGS(SSGSCppCustomGraphGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& inArgs, UEdGraphPin* inGraphPinObj) {
		SGraphPin::Construct(SGraphPin::FArguments(), inGraphPinObj);
	}

protected:
	virtual FSlateColor GetPinColor() const override {
		return FSlateColor(FLinearColor(1.0f, 0.2f, 0.2f));
	}
};

class SSGSCppCustomGraphEndGraphPin : public SGraphPin {
public:
	SLATE_BEGIN_ARGS(SSGSCppCustomGraphGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& inArgs, UEdGraphPin* inGraphPinObj) {
		SGraphPin::Construct(SGraphPin::FArguments(), inGraphPinObj);
	}

protected:
	virtual FSlateColor GetPinColor() const override {
		return FSlateColor(FLinearColor(0.2f, 0.2f, 1.0f));
	}
};

struct FSGSCppCustomGraphPinFactory : public FGraphPanelPinFactory {
public:
	virtual ~FSGSCppCustomGraphPinFactory() {}
	virtual TSharedPtr<SGraphPin> CreatePin(UEdGraphPin* pin) const override {
		if (FName(TEXT("SGSCppCustomGraphPin")) == pin->PinType.PinSubCategory) {
			return SNew(SSGSCppCustomGraphGraphPin, pin);
		} else if (FName(TEXT("StartPin")) == pin->PinType.PinSubCategory) {
			return SNew(SSGSCppCustomGraphStartGraphPin, pin);
		} else if (FName(TEXT("EndPin")) == pin->PinType.PinSubCategory) {
			return SNew(SSGSCppCustomGraphEndGraphPin, pin);
		} else if (FName(TEXT("SGSCppPinCustomData")) == pin->PinType.PinSubCategory) {
			return SNew(SSGSCppCustomGraphContinueDataGraphPin, pin);
		} 
		return nullptr;
	}
};

void FSGSCppCustomGraphAssetEditorModule::StartupModule()
{
	/*
	const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(GLTFEXPORTER_MODULE_NAME);
	FSlateStyleSet::SetContentRoot(Plugin->GetBaseDir() / TEXT("Resources"));

	Set("Icon16", new FSlateImageBrush(FSlateStyleSet::RootToContentDir(TEXT("Icon16.png")), FVector2D(16.0f, 16.0f)));
	*/

	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	IAssetTools& assetToolsModule = IAssetTools::Get();
	EAssetTypeCategories::Type assetType = assetToolsModule.RegisterAdvancedAssetCategory(FName(TEXT("SGSCppGraph")), LOCTEXT("SGSCppGraph", "SGSCppCustomGraph"));
	TSharedPtr<SGSCppCustomGraphAssetAction> SGSCppCustomGraphAssetActionL = MakeShareable(new SGSCppCustomGraphAssetAction(assetType));
	assetToolsModule.RegisterAssetTypeActions(SGSCppCustomGraphAssetActionL.ToSharedRef());

	_styleSet = MakeShareable(new FSlateStyleSet(TEXT("SGSCppCustomGraphAssetEditorStyle")));
	TSharedPtr<IPlugin> plugin = IPluginManager::Get().FindPlugin("SirGasSystem");
	//FString contentDir = plugin->GetContentDir();
	FString contentDir = plugin->GetBaseDir() / TEXT("Resources");
	_styleSet->SetContentRoot(contentDir);

	//FSlateImageBrush* thumbnailBrush = new FSlateImageBrush(_styleSet->RootToContentDir(TEXT("SGSCppCustomGraphAssetThumbnail"), TEXT(".png")), FVector2D(128.0, 128.0));
	FSlateImageBrush* thumbnailBrush = new FSlateImageBrush(_styleSet->RootToContentDir(TEXT("SGSCppCustomGraphAssetThumbnail"), TEXT(".png")), FVector2D(128.0, 128.0));
	FSlateImageBrush* iconBrush = new FSlateImageBrush(_styleSet->RootToContentDir(TEXT("SGSCppCustomGraphAssetIcon"), TEXT(".png")), FVector2D(128.0, 128.0));
	FSlateImageBrush* nodeAddIcon = new FSlateImageBrush(_styleSet->RootToContentDir(TEXT("NodeAddPinIcon"), TEXT(".png")), FVector2D(128.0, 128.0));
	FSlateImageBrush* nodeDeletePinIcon = new FSlateImageBrush(_styleSet->RootToContentDir(TEXT("NodeDeletePinIcon"), TEXT(".png")), FVector2D(128.0, 128.0));
	FSlateImageBrush* nodeDeleteNodeIcon = new FSlateImageBrush(_styleSet->RootToContentDir(TEXT("NodeDeleteNodeIcon"), TEXT(".png")), FVector2D(128.0, 128.0));

	_styleSet->Set(TEXT("ClassThumbnail.SGSCppCustomGraphAsset"), thumbnailBrush);
	_styleSet->Set(TEXT("ClassIcon.SGSCppCustomGraphAsset"), iconBrush);
	_styleSet->Set(TEXT("SGSCppCustomGraphAssetEditor.NodeAddPinIcon"), nodeAddIcon);
	_styleSet->Set(TEXT("SGSCppCustomGraphAssetEditor.NodeDeletePinIcon"), nodeDeletePinIcon);
	_styleSet->Set(TEXT("SGSCppCustomGraphAssetEditor.NodeDeleteNodeIcon"), nodeDeleteNodeIcon);

	FSlateStyleRegistry::RegisterSlateStyle(*_styleSet);

	_pinFactory = MakeShareable(new FSGSCppCustomGraphPinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(_pinFactory);
}

void FSGSCppCustomGraphAssetEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FSlateStyleRegistry::UnRegisterSlateStyle(*_styleSet);
	FEdGraphUtilities::UnregisterVisualPinFactory(_pinFactory);
}

#undef LOCTEXT_NAMESPACE