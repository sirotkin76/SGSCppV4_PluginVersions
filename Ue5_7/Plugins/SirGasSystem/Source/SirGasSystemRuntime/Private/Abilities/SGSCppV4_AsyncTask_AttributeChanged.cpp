// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.


#include "Abilities/SGSCppV4_AsyncTask_AttributeChanged.h"


USGSCppV4_AsyncTask_AttributeChanged* USGSCppV4_AsyncTask_AttributeChanged::ListenForAttributeChange(
	UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute)
{
	USGSCppV4_AsyncTask_AttributeChanged* WaitForAttributeChangedTask = NewObject<USGSCppV4_AsyncTask_AttributeChanged>();
	WaitForAttributeChangedTask->ASC = AbilitySystemComponent;
	WaitForAttributeChangedTask->AttributeToListenFor = Attribute;

	if (!IsValid(AbilitySystemComponent) || !Attribute.IsValid())
	{
		WaitForAttributeChangedTask->RemoveFromRoot();
		return nullptr;
	}

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangedTask, &USGSCppV4_AsyncTask_AttributeChanged::AttributeChanged);

	return WaitForAttributeChangedTask;
}

USGSCppV4_AsyncTask_AttributeChanged* USGSCppV4_AsyncTask_AttributeChanged::ListenForAttributesChange(
	UAbilitySystemComponent* AbilitySystemComponent, TArray<FGameplayAttribute> Attributes)
{
	USGSCppV4_AsyncTask_AttributeChanged* WaitForAttributeChangedTask = NewObject<USGSCppV4_AsyncTask_AttributeChanged>();
	WaitForAttributeChangedTask->ASC = AbilitySystemComponent;
	WaitForAttributeChangedTask->AttributesToListenFor = Attributes;

	if (!IsValid(AbilitySystemComponent) || Attributes.Num() < 1)
	{
		WaitForAttributeChangedTask->RemoveFromRoot();
		return nullptr;
	}

	for (FGameplayAttribute Attribute : Attributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangedTask, &USGSCppV4_AsyncTask_AttributeChanged::AttributeChanged);
	}

	return WaitForAttributeChangedTask;
}

void USGSCppV4_AsyncTask_AttributeChanged::EndTask()
{
	if (IsValid(ASC))
	{
		ASC->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);

		for (FGameplayAttribute Attribute : AttributesToListenFor)
		{
			ASC->GetGameplayAttributeValueChangeDelegate(Attribute).RemoveAll(this);
		}
	}

	SetReadyToDestroy();
	//MarkPendingKill();
	MarkAsGarbage();
}

void USGSCppV4_AsyncTask_AttributeChanged::AttributeChanged(const FOnAttributeChangeData& Data)
{
	OnAttributeChanged.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}
