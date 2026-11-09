// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.


#include "Abilities/SGSCppV4_AbilitySystemComponent.h"
#include "Game/SGSCppV4_Character.h"
#include "AbilitySystemGlobals.h"


USGSCppV4_AbilitySystemComponent::USGSCppV4_AbilitySystemComponent()
{
}

void USGSCppV4_AbilitySystemComponent::GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer,
	TArray<UGameplayAbility*>& ActiveAbilities)
{
	TArray<FGameplayAbilitySpec*> AbilitiesToActivate;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(GameplayTagContainer, AbilitiesToActivate, false);

	// Iterate the list of all ability specs
	for (FGameplayAbilitySpec* Spec : AbilitiesToActivate)
	{
		// Iterate all instances on this ability spec
		TArray<UGameplayAbility*> AbilityInstances = Spec->GetAbilityInstances();

		for (UGameplayAbility* ActiveAbility : AbilityInstances)
		{
			ActiveAbilities.Add(Cast<UGameplayAbility>(ActiveAbility));
		}
	}
}

int32 USGSCppV4_AbilitySystemComponent::GetDefaultAbilityLevel() const
{
	ASGSCppV4_Character* OwningCharacter = Cast<ASGSCppV4_Character>(GetOwnerActor());

	if (OwningCharacter)
	{
		//return OwningCharacter->FSGSCppGetCharacterLevel();
		return 1;
	}
	return 1;
}

USGSCppV4_AbilitySystemComponent* USGSCppV4_AbilitySystemComponent::GetAbilitySystemComponentFromActor(const AActor* Actor,
	bool LookForComponent)
{
	return Cast<USGSCppV4_AbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor, LookForComponent));
}
