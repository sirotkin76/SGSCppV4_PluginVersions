// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.


#include "Game/Components/SGSCppV4_Component_Storage.h"


// Sets default values for this component's properties
USGSCppV4_Component_Storage::USGSCppV4_Component_Storage()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USGSCppV4_Component_Storage::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USGSCppV4_Component_Storage::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<FSGSCppV4InvSlot> USGSCppV4_Component_Storage::SGSInvSys_SlotsGet()
{
	return  FSGSInvSysSlots;
}

void USGSCppV4_Component_Storage::SGSInvSys_SlotsSet(TArray<FSGSCppV4InvSlot> NewItems)
{
	FSGSInvSysSlots = NewItems;
}

void USGSCppV4_Component_Storage::SGSInvSys_SetMaxSlots(int32 SetNewMaxSlot)
{
	MaxSlots = SetNewMaxSlot;
}

int32 USGSCppV4_Component_Storage::SGSInvSys_GetMaxSlots()
{
	return MaxSlots;
}

