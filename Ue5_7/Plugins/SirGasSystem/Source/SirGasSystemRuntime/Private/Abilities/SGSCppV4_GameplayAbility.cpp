// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.


#include "Abilities/SGSCppV4_GameplayAbility.h"

#include "Abilities/SGSCppV4_TargetType.h"
#include "Game/SGSCppV4_Character.h"

USGSCppV4_GameplayAbility::USGSCppV4_GameplayAbility()
{
}

FSGSCppV4_GE_ContainerSpec USGSCppV4_GameplayAbility::MakeEffectContainerSpecFromContainer(
	const FSGSCppGameplayEffectContainerV4& Container, const FGameplayEventData& EventData, int32 OverrideGameplayLevel)
{
	// First figure out our actor info
	FSGSCppV4_GE_ContainerSpec ReturnSpec;
	
	AActor* OwningActor = GetOwningActorFromActorInfo();
	ASGSCppV4_Character* OwningCharacter = Cast<ASGSCppV4_Character>(OwningActor);
	USGSCppV4_AbilitySystemComponent* OwningASC = USGSCppV4_AbilitySystemComponent::GetAbilitySystemComponentFromActor(OwningActor);
	
	if (OwningASC)
	{
		// If we have a target type, run the targeting logic. This is optional, targets can be added later
		if (Container.TargetType.Get())
		{
			TArray<FHitResult> HitResults;
			TArray<AActor*> TargetActors;
			const USGSCppV4_TargetType* TargetTypeCDO = Container.TargetType.GetDefaultObject();
			AActor* AvatarActor = GetAvatarActorFromActorInfo();
			TargetTypeCDO->GetTargets(OwningCharacter, AvatarActor, EventData, HitResults, TargetActors);
			
			ReturnSpec.AddTargets(HitResults, TargetActors);
		}

		// If we don't have an override level, use the default on the ability itself
		if (OverrideGameplayLevel == INDEX_NONE)
		{
			OverrideGameplayLevel = OverrideGameplayLevel = this->GetAbilityLevel(); //OwningASC->GetDefaultAbilityLevel();
		}

		// Build GameplayEffectSpecs for each applied effect
		for (const TSubclassOf<UGameplayEffect>& EffectClass : Container.TargetGameplayEffectClasses)
		{
			ReturnSpec.TargetGameplayEffectSpecs.Add(MakeOutgoingGameplayEffectSpec(EffectClass, OverrideGameplayLevel));
		}
	}
	return ReturnSpec;
}

FSGSCppV4_GE_ContainerSpec USGSCppV4_GameplayAbility::MakeEffectContainerSpec(FGameplayTag ContainerTag,
                                                                                       const FGameplayEventData& EventData, int32 OverrideGameplayLevel)
{
	FSGSCppGameplayEffectContainerV4* FoundContainer = EffectContainerMap.Find(ContainerTag);

	if (FoundContainer)
	{
		return MakeEffectContainerSpecFromContainer(*FoundContainer, EventData, OverrideGameplayLevel);
	}
	return FSGSCppV4_GE_ContainerSpec();
}

TArray<FActiveGameplayEffectHandle> USGSCppV4_GameplayAbility::ApplyEffectContainerSpec(
	const FSGSCppV4_GE_ContainerSpec& ContainerSpec)
{
	TArray<FActiveGameplayEffectHandle> AllEffects;

	// Iterate list of effect specs and apply them to their target data
	for (const FGameplayEffectSpecHandle& SpecHandle : ContainerSpec.TargetGameplayEffectSpecs)
	{
		AllEffects.Append(K2_ApplyGameplayEffectSpecToTarget(SpecHandle, ContainerSpec.TargetData));
	}
	return AllEffects;
}

TArray<FActiveGameplayEffectHandle> USGSCppV4_GameplayAbility::ApplyEffectContainer(FGameplayTag ContainerTag,
	const FGameplayEventData& EventData, int32 OverrideGameplayLevel)
{
	FSGSCppV4_GE_ContainerSpec Spec = MakeEffectContainerSpec(ContainerTag, EventData, OverrideGameplayLevel);
	return ApplyEffectContainerSpec(Spec);
}
