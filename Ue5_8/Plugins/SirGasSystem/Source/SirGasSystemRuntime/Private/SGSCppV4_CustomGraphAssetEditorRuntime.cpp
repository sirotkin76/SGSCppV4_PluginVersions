// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#include "SGSCppV4_CustomGraphAssetEditorRuntime.h"

//IMPLEMENT_MODULE(FSGSCppCustomGraphAssetEditorRuntimeModule, SGSCppCustomGraphAssetEditorRuntime)
IMPLEMENT_MODULE(FSGSCppCustomGraphAssetEditorRuntimeModule, SirGasSystemRuntime)

#define LOCTEXT_NAMESPACE "FSGSCppCustomGraphAssetEditorRuntimeModule"

void FSGSCppCustomGraphAssetEditorRuntimeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FSGSCppCustomGraphAssetEditorRuntimeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	