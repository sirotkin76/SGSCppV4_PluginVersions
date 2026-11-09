// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.


#include "Game/Actors/SGSCppV4_ActorInteractable_Storage.h"
#include "Game/Components/SGSCppV4_Component_Character_Init.h"


// Sets default values
ASGSCppV4_ActorInteractable_Storage::ASGSCppV4_ActorInteractable_Storage()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SgsCppInitComponentV4 = CreateDefaultSubobject<USGSCppV4_Component_Character_Init>(TEXT("SGSCppV4_InitComponent"));
	
}

// Called when the game starts or when spawned
void ASGSCppV4_ActorInteractable_Storage::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASGSCppV4_ActorInteractable_Storage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

