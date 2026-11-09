// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "Net/UnrealNetwork.h"
#include "SGSCppV4_Interface_Interactable.generated.h"

/**
 * 
 */

UINTERFACE()
class USGSCppV4_Interface_Interactable : public UInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Actionable")

};

class SIRGASSYSTEMRUNTIME_API ISGSCppV4_Interface_Interactable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="SGSCppV4|ICppInteractable|0")
	void EvIInteractableStart_v0();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="SGSCppV4|ICppInteractable|0")
	void EvIInteractableEnd_v0();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="SGSCppV4|ICppInteractable|1")
	void EvIInteractableActivate_v1();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="SGSCppV4|ICppInteractable|1")
	void EvIInteractableDeactivate_v1();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="SGSCppV4|ICppInteractable|2")
	void EvIInteractableInitialization_v3();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="SGSCppV4|ICppInteractable|2")
	void EvIInteractableDeinitialize_v3();
	
};

