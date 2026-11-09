// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.


#include "Game/Actors/SGSCppV4_ActorInteractable.h"


// Sets default values
ASGSCppV4_ActorInteractable::ASGSCppV4_ActorInteractable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASGSCppV4_ActorInteractable::BeginPlay()
{
	Super::BeginPlay();

	UniqueId = TEXT(""+GetUniqueID());
	
}

// Called every frame
void ASGSCppV4_ActorInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

