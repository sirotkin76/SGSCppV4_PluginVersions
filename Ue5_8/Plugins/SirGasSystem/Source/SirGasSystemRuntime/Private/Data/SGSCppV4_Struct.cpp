// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.


#include "Data/SGSCppV4_Struct.h"


FSGSCppV4_GE_ContainerSpec::FSGSCppV4_GE_ContainerSpec()
{
}

bool FSGSCppV4_GE_ContainerSpec::HasValidEffects() const
{
	return TargetGameplayEffectSpecs.Num() > 0;
}

bool FSGSCppV4_GE_ContainerSpec::HasValidTargets() const
{
	return TargetData.Num() > 0;
}

void FSGSCppV4_GE_ContainerSpec::AddTargets(const TArray<FHitResult>& HitResults, const TArray<AActor*>& TargetActors)
{
	for (const FHitResult& HitResult : HitResults)
	{
		FGameplayAbilityTargetData_SingleTargetHit* NewData = new FGameplayAbilityTargetData_SingleTargetHit(HitResult);
		TargetData.Add(NewData);
	}

	if (TargetActors.Num() > 0)
	{
		FGameplayAbilityTargetData_ActorArray* NewData = new FGameplayAbilityTargetData_ActorArray();
		NewData->TargetActorArray.Append(TargetActors);
		TargetData.Add(NewData);
	}
}