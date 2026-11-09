// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SGSCppCustomGraphAssetFactory.generated.h"

UCLASS()
class USGSCppCustomGraphAssetFactory : public UFactory {
    GENERATED_BODY()

public:
    USGSCppCustomGraphAssetFactory(const FObjectInitializer& objectInitializer);

public: // UFactory interface
    virtual UObject* FactoryCreateNew(UClass* uclass, UObject* inParent, FName name, EObjectFlags flags, UObject* context, FFeedbackContext* warn) override;
    virtual bool CanCreateNew() const override;
};
