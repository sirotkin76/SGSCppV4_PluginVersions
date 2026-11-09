// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "Net/UnrealNetwork.h"
#include "Data/SGSCppV4_Struct.h"
#include "Components/ActorComponent.h"
#include "SGSCppV4_Component_Storage.generated.h"

class USGSCppV4_DataAsset_Attr;
class USGSCppV4_DataAsset_Attr_InventorySlot;


UCLASS(MinimalAPI, ClassGroup=("FSGSCpp|InventarySystem"), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType, meta = (ShowWorldContextPin)  )
class USGSCppV4_Component_Storage : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USGSCppV4_Component_Storage();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSGSCpp|InventarySystem|Variables")
	UPROPERTY()
	TArray<FSGSCppV4InvSlot> FSGSInvSysSlots;

	UPROPERTY()
	int32 MaxSlots;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FSGSCpp|InventarySystem|Functions", meta = (DisplayName = "SGS InvSys Slots Get V4"))
	TArray<FSGSCppV4InvSlot> SGSInvSys_SlotsGet();
		
	UFUNCTION(BlueprintCallable, Category = "FSGSCpp|InventarySystem|Functions", meta = (DisplayName = "SGS InvSys Slots Set V4"))
	void SGSInvSys_SlotsSet(TArray<FSGSCppV4InvSlot> NewItems);
		
	UFUNCTION(BlueprintCallable, Category = "FSGSCpp|InventarySystem|Functions", meta = (DisplayName = "SGS InvSys Slots Max Set V4"))
	void SGSInvSys_SetMaxSlots(int32 SetNewMaxSlot);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FSGSCpp|InventarySystem|Functions", meta = (DisplayName = "SGS InvSys Slots Max Get V4"))
	int32 SGSInvSys_GetMaxSlots();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "FSGSCpp|InventarySystem|Events")
	void EvUpdateLevel(int32 SetNewLevel);

	
};
