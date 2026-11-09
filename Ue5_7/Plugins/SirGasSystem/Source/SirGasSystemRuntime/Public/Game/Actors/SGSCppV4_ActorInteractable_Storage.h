// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "SGSCppV4_ActorInteractable.h"
#include "Net/UnrealNetwork.h"
#include "SGSCppV4_ActorInteractable_Storage.generated.h"

class USGSCppV4_Component_Character_Init;

UCLASS()
class SIRGASSYSTEMRUNTIME_API ASGSCppV4_ActorInteractable_Storage : public ASGSCppV4_ActorInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASGSCppV4_ActorInteractable_Storage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY()
	USGSCppV4_Component_Character_Init* SgsCppInitComponentV4;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
