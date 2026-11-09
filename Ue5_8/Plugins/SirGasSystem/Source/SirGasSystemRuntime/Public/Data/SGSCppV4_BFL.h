// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "Net/UnrealNetwork.h"
#include "SGSCppV4_Enumerations.h"
#include "SGSCppV4_Struct.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SGSCppV4_BFL.generated.h"

class USGSCppV4_Component_Storage;

/**
 * 
 */
UCLASS(Blueprintable, Category = "SGSCpp|BFL")
class SIRGASSYSTEMRUNTIME_API USGSCppV4_BFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		
public:
	
	UFUNCTION(BlueprintCallable, Category="SGSCpp|BFLInvSysV4")
	static void SGSCppBFLInvSysSlotsSetV4(USGSCppV4_Component_Storage * Owner, TArray<FSGSCppV4InvSlot> ArrNewInvSlots);

	UFUNCTION(BlueprintCallable, Category="SGSCpp|Base")
	static ESGSSirDirectionMovement SGSCppBFLGetDirectionMovementV4(float ForwardL, float RightL);

	/*
	UFUNCTION(BlueprintCallable, Category="SGSCpp|BFLInvSysV4|Slot")
	static void SGSCppBFLInvSysSlotCheckNameV4(USGSCppSirInvSysV4 * Owner, FName FindName,
	bool &ResFindName, FSGSInvSysSlot &ResInvSlotData, int32 &ResIndexInSlots);

	UFUNCTION(BlueprintCallable, Category="SGSCpp|BFLInvSysV4|Slot")
	static void SGSCppBFLInvSysSlotAddNotStackableV4(USGSCppSirInvSysV4 * NewOwner, FSGSInvSysSlot NewSlot, bool &Added);
	
	UFUNCTION(BlueprintCallable, Category="SGSCpp|BFLInvSysV4|Slot")
	static void SGSCppBFLInvSysSlotAddV4(USGSCppSirInvSysV4 * inOwner, FSGSInvSysSlot inInvSlot);
	
	UFUNCTION(BlueprintCallable, Category="SGSCpp|BFLInvSysV4|Slot")
	static void SGSCppBFLInvSysSlotsReplaceNotStackableV4(USGSCppSirInvSysV4 * inNewOwner, FSGSInvSysSlot inNewSlot, USGSCppSirInvSysV4 * inOldOwner, FSGSInvSysSlot inOldSlot);
	
	UFUNCTION(BlueprintCallable, Category="SGSCpp|BFLInvSysV4|Slot", meta = (DisplayName = "SGS InvSys Slots Delete - Clear slot  V4"))
	static void SGSCppBFLInvSysSlotClearV4(USGSCppSirInvSysV4 * inOwner, int32 inInvSlotIndex);
	
	UFUNCTION(BlueprintCallable, Category="SGSCpp|BFLInvSysV4|Slot")
	static void SGSCppBFLInvSysSlotSetNewDataV4(USGSCppSirInvSysV4 * inOwner, FSGSInvSysSlot inOldInvSlot, FSGSInvSysSlot inNewInvSlot);

	UFUNCTION(BlueprintCallable, Category="SGSCpp|BFLInvSysV4|Count")
	static void SGSCppBFLInvSysSlotCountSetV4(USGSCppSirInvSysV4 * inOwner, FSGSInvSysSlot inInvSlot, int32 inSetNewCount);

	UFUNCTION(BlueprintCallable, Category="SGSCpp|BFLInvSysV4|Slot")
	static void SGSCppBFLInvSysSlotReplaceV4(USGSCppSirInvSysV4 * inOldOwner, USGSCppSirInvSysV4 * inNewOwner, int32 inNewIndex, FVector2D inNewGrid, FSGSInvSysSlot inOldInvSlot);

	UFUNCTION(BlueprintCallable, Category="SGSCpp|BFLInvSysV4|Slot")
	static void SGSCppBFLInvSysFreeSlotSetV4(USGSCppSirInvSysV4 * inOldOwner, USGSCppSirInvSysV4 * inNewOwner, FSGSInvSysSlot inOldInvSlot, int32 inNewIndex);
	*/

};
 