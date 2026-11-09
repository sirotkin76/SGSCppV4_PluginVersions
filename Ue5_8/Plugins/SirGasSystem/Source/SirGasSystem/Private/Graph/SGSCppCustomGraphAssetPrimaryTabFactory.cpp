// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#include "Graph/SGSCppCustomGraphAssetPrimaryTabFactory.h"
#include "Graph/SGSCppCustomGraphAssetEditorApp.h"
#include "Graph/SGSCppV4_CustomGraphAsset.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "GraphEditor.h"
#include "Editor/UnrealEd/Public/Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"

SGSCppCustomGraphAssetPrimaryTabFactory::SGSCppCustomGraphAssetPrimaryTabFactory(TSharedPtr<SGSCppCustomGraphAssetEditorApp> app) : FWorkflowTabFactory(FName("SGSCppCustomGraphAssetPrimaryTab"), app) {
    _app = app;

    TabLabel = FText::FromString(TEXT("Primary"));

	ViewMenuDescription = FText::FromString(TEXT("Displays a primary view for whatever you want to do."));
	ViewMenuTooltip = FText::FromString(TEXT("Show the primary view."));
}

TSharedRef<SWidget> SGSCppCustomGraphAssetPrimaryTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const {
    TSharedPtr<SGSCppCustomGraphAssetEditorApp> app = _app.Pin();

    SGraphEditor::FGraphEditorEvents graphEvents;
    graphEvents.OnSelectionChanged.BindRaw(app.Get(), &SGSCppCustomGraphAssetEditorApp::OnGraphSelectionChanged);

    TSharedPtr<SGraphEditor> graphEditor = 
        SNew(SGraphEditor)
            .IsEditable(true)
            .GraphEvents(graphEvents)
            .GraphToEdit(app->GetWorkingGraph());
    app->SetWorkingGraphUi(graphEditor);

    return SNew(SVerticalBox)
                + SVerticalBox::Slot()
                .FillHeight(1.0f)
                .HAlign(HAlign_Fill)
                [
                    graphEditor.ToSharedRef()
                ];
}

FText SGSCppCustomGraphAssetPrimaryTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const {
    return FText::FromString(TEXT("A primary view for doing primary things."));
}
