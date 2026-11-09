// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "Net/UnrealNetwork.h"
#include "Data/SGSCppV4_Interface_Interactable.h"
#include "GameFramework/Actor.h"
#include "SGSCppV4_ActorInteractable.generated.h"

UCLASS()
class SIRGASSYSTEMRUNTIME_API ASGSCppV4_ActorInteractable : public AActor, public ISGSCppV4_Interface_Interactable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASGSCppV4_ActorInteractable();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Attr", meta = (AllowPrivateAccess = "true"))
	FString UniqueId;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
