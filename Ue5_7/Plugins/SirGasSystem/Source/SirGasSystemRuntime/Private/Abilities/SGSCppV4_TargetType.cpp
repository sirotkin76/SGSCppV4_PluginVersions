// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.


#include "Abilities/SGSCppV4_TargetType.h"
#include "Abilities/SGSCppV4_GameplayAbility.h"
#include "Game/SGSCppV4_Character.h"

void USGSCppV4_TargetType::GetTargets_Implementation(
	ASGSCppV4_Character* TargetingCharacter,
	AActor* TargetingActor,
	FGameplayEventData EventData,
	TArray<FHitResult>& OutHitResults,
	TArray<AActor*>& OutActors
	) const
{
	return;
}

void USGSCppTargetType_UseOwner::GetTargets_Implementation(
	ASGSCppV4_Character* TargetingCharacterLocal,
	AActor* TargetingActor,
	FGameplayEventData EventData,
	TArray<FHitResult>& OutHitResults,
	TArray<AActor*>& OutActors
	) const
{
	OutActors.Add(TargetingCharacterLocal);
}

void USGSCppTargetType_UseEventData::GetTargets_Implementation(
	ASGSCppV4_Character* TargetingCharacter,
	AActor* TargetingActor,
	FGameplayEventData EventData,
	TArray<FHitResult>& OutHitResults,
	TArray<AActor*>& OutActors
	) const
{
	const FHitResult* FoundHitResult = EventData.ContextHandle.GetHitResult();
	if (FoundHitResult)
	{
		OutHitResults.Add(*FoundHitResult);
	}
	else if (EventData.Target)
	{
		OutActors.Add(const_cast<AActor*>(EventData.Target.Get()));
	}
}

