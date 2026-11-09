// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "Net/UnrealNetwork.h"
#include "Abilities/GameplayAbilityTypes.h"

#include "SGSCppV4_TargetType.generated.h"


/**
 * Class that is used to determine targeting for abilities
 * It is meant to be blueprinted to run target logic
 * This does not subclass GameplayAbilityTargetActor because this class is never instanced into the world
 * This can be used as a basis for a game-specific targeting blueprint
 * If your targeting is more complicated you may need to instance into the world once or as a pooled actor 
 */

class ASGSCppV4_Character;

UCLASS(Blueprintable, meta = (ShowWorldContextPin))
class SIRGASSYSTEMRUNTIME_API USGSCppV4_TargetType : public UObject
{
	GENERATED_BODY()
	
public:
	// Constructor and overrides
	USGSCppV4_TargetType() {};

	/** Called to determine targets to apply gameplay effects to */
	UFUNCTION(BlueprintNativeEvent)
	void GetTargets(
		ASGSCppV4_Character* TargetingCharacter,
		AActor* TargetingActor,
		FGameplayEventData EventData,
		TArray<FHitResult>& OutHitResults,
		TArray<AActor*>& OutActors
		) const;
};

/** Trivial target type that uses the owner */
UCLASS(NotBlueprintable)
class SIRGASSYSTEMRUNTIME_API USGSCppTargetType_UseOwner : public USGSCppV4_TargetType
{
	GENERATED_BODY()

public:
	// Constructor and overrides
	USGSCppTargetType_UseOwner() {}

	/** Uses the passed in event data */
	virtual void GetTargets_Implementation(
		ASGSCppV4_Character* TargetingCharacter, 
		AActor* TargetingActor,
		FGameplayEventData EventData,
		TArray<FHitResult>& OutHitResults,
		TArray<AActor*>& OutActors
		) const override;
};

/** Trivial target type that pulls the target out of the event data */
UCLASS(NotBlueprintable)
class SIRGASSYSTEMRUNTIME_API USGSCppTargetType_UseEventData : public USGSCppV4_TargetType
{
	GENERATED_BODY()

public:
	// Constructor and overrides
	USGSCppTargetType_UseEventData() {}

	/** Uses the passed in event data */
	virtual void GetTargets_Implementation(
		ASGSCppV4_Character* TargetingCharacter,
		AActor* TargetingActor,
		FGameplayEventData EventData,
		TArray<FHitResult>& OutHitResults,
		TArray<AActor*>& OutActors
		) const override;
};
