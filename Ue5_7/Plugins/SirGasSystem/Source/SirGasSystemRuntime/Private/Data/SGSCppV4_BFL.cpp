// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.


#include "Data/SGSCppV4_BFL.h"

#include "Data/SGSCppV4_Enumerations.h"
#include "Game/Components/SGSCppV4_Component_Storage.h"


void USGSCppV4_BFL::SGSCppBFLInvSysSlotsSetV4(USGSCppV4_Component_Storage * Owner,
                                              TArray<FSGSCppV4InvSlot> ArrNewInvSlots)
{
	Owner->SGSInvSys_SlotsSet(ArrNewInvSlots);
}

ESGSSirDirectionMovement USGSCppV4_BFL::SGSCppBFLGetDirectionMovementV4(float ForwardL, float RightL)
{
	if (ForwardL == -1.f && RightL == 0.f) return ESGSSirDirectionMovement::Back_None;
	if (ForwardL == -1.f && RightL == 1.f) return ESGSSirDirectionMovement::Back_Right;
	if (ForwardL == -1.f && RightL == -1.f) return ESGSSirDirectionMovement::Back_Left;
	
	if (ForwardL == 0.f && RightL == -1.f) return ESGSSirDirectionMovement::None_Left;
	if (ForwardL == 0.f && RightL == 1.f) return ESGSSirDirectionMovement::None_Right;
	
	if (ForwardL == 1.f && RightL == 1.f) return ESGSSirDirectionMovement::Forward_Right;
	if (ForwardL == 1.f && RightL == -1.f) return ESGSSirDirectionMovement::Forward_Left;

	return ESGSSirDirectionMovement::Forward_None;
}

/*
void USGSCppSirInvSysBFLV4::SGSCppBFLInvSysSlotCheckNameV4(USGSCppSirInvSysV4* Owner, FName FindName,
	bool &ResFindName, FSGSInvSysSlot &ResInvSlotData, int32 &ResIndexInSlots)
{
	if (!IsValid(Owner))
	{
		ResFindName = false;
		return;
	};		
	int32 indexLocal = 0;
	
	//for (TSubclassOf<UGameplayEffect> GameplayEffect : GameplayEffectsL)
		
	for (FSGSInvSysSlot slotsL : Owner->SGSInvSys_SlotsGet()) 
	{
		if (slotsL.SlotName == FindName)
		{
			// Дата ассет
			if (!IsValid(slotsL.SGSCppV4_InvSlot_DataAsset))
			{
				ResFindName = false;
				return;
			};
			
			ResIndexInSlots = indexLocal;
			ResInvSlotData = slotsL;
				
			ResFindName = true;
			return;
		};
		
		indexLocal++;
	}

	ResFindName = false;
}

void USGSCppSirInvSysBFLV4:: SGSCppBFLInvSysSlotAddNotStackableV4(USGSCppSirInvSysV4 * NewOwner,
	FSGSInvSysSlot NewSlot, bool& Added)
{
	if (!IsValid(NewOwner)) return;
	
	bool AddedLocal = false;

	if (NewOwner->SGSInvSys_SlotsGet().Num() < NewOwner->SGSInvSys_GetMaxSlots())
	{
		// Есть место для записи нового слота
		// и слоты изначально не были созданы пустыми (под разную логику)
		
		NewOwner->FSGSInvSysSlots.Add(NewSlot);
		Added = true;
		return;
	}
	else
	{
		// возможно слоты изначально были созданы пустыми
		TArray<FSGSInvSysSlot> slotsL = NewOwner->SGSInvSys_SlotsGet();
		
		for (int32 i = 0; i < NewOwner->SGSInvSys_SlotsGet().Num(); i++)
		{
			FSGSInvSysSlot slotL = slotsL[i];
			
			// Если дата ассета нет, значить слот пустой, можно записать туда данные 
			if (!IsValid(slotL.SGSCppV4_InvSlot_DataAsset))
			{
				FSGSInvSysSlot NewSlotL = NewSlot;
				NewSlotL.SlotIndex = i;
				slotsL[i] = NewSlotL;
				NewOwner->SGSInvSys_SlotsSet(slotsL);
				
				Added = true;
				return;
			}
		}
	}
	
	Added = false;
	return;
	
}

void USGSCppSirInvSysBFLV4::SGSCppBFLInvSysSlotAddV4(USGSCppSirInvSysV4* inOwner, FSGSInvSysSlot inInvSlot)
{
	if (!IsValid(inOwner)) return;
	
	inOwner->FSGSInvSysSlots.Add(inInvSlot);
}

void USGSCppSirInvSysBFLV4::SGSCppBFLInvSysSlotsReplaceNotStackableV4(USGSCppSirInvSysV4* inNewOwner,
                                                                      FSGSInvSysSlot inNewSlot, USGSCppSirInvSysV4* inOldOwner, FSGSInvSysSlot inOldSlot)
{
	FSGSInvSysSlot inNewSlotL = inNewSlot;
	FSGSInvSysSlot inOldSlotL = inOldSlot;
	
	SGSCppBFLInvSysSlotSetNewDataV4(inNewOwner, inNewSlotL, inOldSlotL);
	SGSCppBFLInvSysSlotSetNewDataV4(inOldOwner, inOldSlotL, inNewSlotL);
	
}

void USGSCppSirInvSysBFLV4::SGSCppBFLInvSysSlotCountSetV4(USGSCppSirInvSysV4* inOwner, FSGSInvSysSlot InvSlot,
                                                          int32 SetNewCount)
{
	if (!IsValid(inOwner)) return;
	
	TArray<FSGSInvSysSlot> FSGSInvSysSlotsL = inOwner->SGSInvSys_SlotsGet();
	FSGSInvSysSlot InvSlotLocalClear;
	
	
	int32 indexLocal = InvSlot.SlotIndex;

	if (InvSlot.SlotIndex < FSGSInvSysSlotsL.Num() )
	{
		FSGSInvSysSlotsL.Insert(InvSlotLocalClear, indexLocal);
	};

	if (InvSlot.SlotIndex < FSGSInvSysSlotsL.Num() ) return;
		
	FSGSInvSysSlotsL[InvSlot.SlotIndex].SGSCppV4_InvSlot_DataAsset = InvSlot.SGSCppV4_InvSlot_DataAsset;
	FSGSInvSysSlotsL[InvSlot.SlotIndex].SlotCount = SetNewCount;
	FSGSInvSysSlotsL[InvSlot.SlotIndex].SlotCondition = InvSlot.SlotCondition;
	FSGSInvSysSlotsL[InvSlot.SlotIndex].SlotName = InvSlot.SlotName;
	
	inOwner->SGSInvSys_SlotsSet(FSGSInvSysSlotsL);

}

void USGSCppSirInvSysBFLV4::SGSCppBFLInvSysSlotClearV4(USGSCppSirInvSysV4* inOwner, int32 inInvSlotIndex)
{
	if (!IsValid(inOwner)) return;

	TArray<FSGSInvSysSlot> FSGSInvSysSlotsL = inOwner->SGSInvSys_SlotsGet();
	FSGSInvSysSlot InvSlotLocalClear;
	

	if (FSGSInvSysSlotsL.Num() <= inInvSlotIndex )
	{
		for (int32 indexLocaCountl = FSGSInvSysSlotsL.Num(); indexLocaCountl < inInvSlotIndex; indexLocaCountl = FSGSInvSysSlotsL.Num() )
		{
			FSGSInvSysSlotsL.Add(InvSlotLocalClear);
		};
	};
	
	FSGSInvSysSlotsL[inInvSlotIndex].SGSCppV4_InvSlot_DataAsset = nullptr;
	FSGSInvSysSlotsL[inInvSlotIndex].SlotCount = -1;
	FSGSInvSysSlotsL[inInvSlotIndex].SlotCondition = -1;
	FSGSInvSysSlotsL[inInvSlotIndex].SlotIndex = inInvSlotIndex;
	FSGSInvSysSlotsL[inInvSlotIndex].SlotName = "";

	inOwner->SGSInvSys_SlotsSet(FSGSInvSysSlotsL);
	
}

void USGSCppSirInvSysBFLV4::SGSCppBFLInvSysSlotSetNewDataV4(USGSCppSirInvSysV4* inOwner,
	FSGSInvSysSlot inOldInvSlot, FSGSInvSysSlot inNewInvSlot)
{
	if (!IsValid(inOwner)) return;

	TArray<FSGSInvSysSlot> FSGSInvSysSlotsL = inOwner->SGSInvSys_SlotsGet();

	/*
	FSGSInvSysSlotsL[inNewInvSlot.SlotIndex].SGSCppV4_InvSlot_DataAsset = inOldInvSlot.SGSCppV4_InvSlot_DataAsset;
	FSGSInvSysSlotsL[inNewInvSlot.SlotIndex].SlotCount = inOldInvSlot.SlotCount;
	FSGSInvSysSlotsL[inNewInvSlot.SlotIndex].SlotCondition = inOldInvSlot.SlotCondition;
	
	FSGSInvSysSlotsL[inNewInvSlot.SlotIndex].SlotIndex = inNewInvSlot.SlotIndex;
	
	FSGSInvSysSlotsL[inNewInvSlot.SlotIndex].SlotName = inOldInvSlot.SlotName;;

	inOwner->SGSInvSys_SlotsSet(FSGSInvSysSlotsL);
	#1#
	FSGSInvSysSlotsL[inOldInvSlot.SlotIndex].SGSCppV4_InvSlot_DataAsset = inNewInvSlot.SGSCppV4_InvSlot_DataAsset;
	FSGSInvSysSlotsL[inOldInvSlot.SlotIndex].SlotCount = inNewInvSlot.SlotCount;
	FSGSInvSysSlotsL[inOldInvSlot.SlotIndex].SlotCondition = inNewInvSlot.SlotCondition;
	
	FSGSInvSysSlotsL[inOldInvSlot.SlotIndex].SlotIndex = inOldInvSlot.SlotIndex;
	
	FSGSInvSysSlotsL[inOldInvSlot.SlotIndex].SlotName = inNewInvSlot.SlotName;;

	inOwner->SGSInvSys_SlotsSet(FSGSInvSysSlotsL);
}

void USGSCppSirInvSysBFLV4::SGSCppBFLInvSysSlotReplaceV4(USGSCppSirInvSysV4* inOldOwner, USGSCppSirInvSysV4* inNewOwner,
	int32 inNewIndex, FVector2D inNewGrid, FSGSInvSysSlot inOldInvSlot)
{
	if (!IsValid(inOldOwner)) return;
	if (!IsValid(inNewOwner)) return;

	TArray<FSGSInvSysSlot> FSGSInvSysSlotsL = inOldOwner->SGSInvSys_SlotsGet();
	
}

void USGSCppSirInvSysBFLV4::SGSCppBFLInvSysFreeSlotSetV4(USGSCppSirInvSysV4* inOldOwner, USGSCppSirInvSysV4* inNewOwner,
	FSGSInvSysSlot inOldInvSlot, int32 inNewIndex)
{
	if (!IsValid(inOldOwner)) return;
	if (!IsValid(inNewOwner)) return;

	FSGSInvSysSlot inOldInvSlotLocal;

	TArray<FSGSInvSysSlot> FSGSInvSysSlotsL = inNewOwner->SGSInvSys_SlotsGet();

	if (FSGSInvSysSlotsL.Num() < inNewIndex)
	{
		int32 localInt = FSGSInvSysSlotsL.Num() - inNewIndex;

		for(int32 i = 0; i < localInt; i++)
		{
			FSGSInvSysSlotsL.Add(inOldInvSlotLocal);
		}
		
	}

	FSGSInvSysSlotsL[inNewIndex].SGSCppV4_InvSlot_DataAsset =	inOldInvSlot.SGSCppV4_InvSlot_DataAsset;
	FSGSInvSysSlotsL[inNewIndex].SlotCount =						inOldInvSlot.SlotCount;
	FSGSInvSysSlotsL[inNewIndex].SlotCondition =					inOldInvSlot.SlotCondition;
	FSGSInvSysSlotsL[inNewIndex].SlotName =							inOldInvSlot.SlotName;;
	
	FSGSInvSysSlotsL[inNewIndex].SlotIndex =						inNewIndex;

	inNewOwner->SGSInvSys_SlotsSet(FSGSInvSysSlotsL);

	// обнуляем, чистим, удаляем старый слот
	SGSCppBFLInvSysSlotClearV4(inOldOwner, inOldInvSlot.SlotIndex);
}
*/































