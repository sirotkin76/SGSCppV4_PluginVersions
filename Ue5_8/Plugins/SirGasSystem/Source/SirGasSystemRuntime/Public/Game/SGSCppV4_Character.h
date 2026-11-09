// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"

#include "GenericTeamAgentInterface.h"
#include "AbilitySystemInterface.h"
#include "Abilities/SGSCppV4_AttributeSet.h"
#include "Abilities/SGSCppV4_AbilitySystemComponent.h"
#include "Data/SGSCppV4_Interface_GameplayAbility.h"

#include "SGSCppV4_Character.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class USGSCppV4_Component_Character_Init;

UCLASS()
class SIRGASSYSTEMRUNTIME_API ASGSCppV4_Character : public ACharacter, public IAbilitySystemInterface, public IGenericTeamAgentInterface, public ISGSCppV4_Interface_GameplayAbility
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	ASGSCppV4_Character();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	virtual void OnRep_Controller() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Implement IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FSGSCpp")
	USGSCppV4_Component_Character_Init* SGSCppV4_Component_Character_Init;

	UFUNCTION(BlueprintPure, Category = "FSGSCpp|Getter")
	USGSCppV4_AbilitySystemComponent* GetSGSCppAbilitySystemComponent();
	
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "SGSCppV4|InterfaceFunction")
	USGSCppV4_Component_Character_Init* SGSCppV4_Bfl_GetGameplayAbility_Implementation() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**
	 * Called when character takes damage, which may have killed them
	 *
	 * @param DamageAmount Amount of damage that was done, not clamped based on current health
	 * @param HitInfo The hit info that generated this damage
	 * @param DamageTags The gameplay tags of the event that did the damage
	 * @param InstigatorCharacter The character that initiated this damage
	 * @param DamageCauser The actual actor that did the damage, might be a weapon or projectile
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "FSGSCpp|Event")
	void FSGSCppOnDamaged(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ASGSCppV4_Character* InstigatorCharacter, AActor* DamageCauser);

	/**
	 * Called when health is changed, either from healing or from being damaged
	 * For damage this is called in addition to OnDamaged/OnKilled
	 *
	 * @param DeltaValue Change in health value, positive for heal, negative for cost. If 0 the delta is unknown
	 * @param EventTags The gameplay tags of the event that changed mana
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "FSGSCpp|Event")
	void FSGSCppOnHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	/**
	 * Called when mana is changed, either from healing or from being used as a cost
	 *
	 * @param DeltaValue Change in mana value, positive for heal, negative for cost. If 0 the delta is unknown
	 * @param EventTags The gameplay tags of the event that changed mana
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "FSGSCpp|Event")
	void FSGSCppOnManaChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	

	UFUNCTION(BlueprintImplementableEvent, Category = "FSGSCpp|Event")
	void FSGSCppOnStaminaChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "FSGSCpp|Event")
	void FSGSCppOnWaterChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "FSGSCpp|Event")
	void FSGSCppOnFoodChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	UFUNCTION(BlueprintImplementableEvent, Category = "FSGSCpp|Event")
	void FSGSCppOnOxygenChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	
	/**
	 * Called when movement speed is changed
	 *
	 * @param DeltaValue Change in move speed
	 * @param EventTags The gameplay tags of the event that changed mana
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "FSGSCpp|Event")
	void FSGSCppOnMoveSpeedChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	/**
	* Getter
	*/

	UFUNCTION(BlueprintPure, Category = "FSGSCpp|Getter")
	USGSCppV4_AttributeSet* FSGSCppGetAttributeSet();

	UFUNCTION(BlueprintPure, Category = "FSGSCpp|Getter")
	virtual bool FSGSCppGetIsAlive();
	

protected:
	/** The component used to handle ability system interactions */
	UPROPERTY()
	USGSCppV4_AbilitySystemComponent* AbilitySystemComponent;

	/** List of attributes modified by the ability system */
	UPROPERTY()
	USGSCppV4_AttributeSet* AttributeSet;

	// Called from RPGAttributeSet, these call BP events above
	virtual void HandleDamage(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ASGSCppV4_Character* InstigatorCharacter, AActor* DamageCauser);
	virtual void HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	virtual void HandleManaChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	virtual void HandleMoveSpeedChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	virtual void HandleStaminaChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	virtual void HandleWaterChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	virtual void HandleFoodChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	virtual void HandleOxygenChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	/** Required to support AIPerceptionSystem */
	virtual FGenericTeamId GetGenericTeamId() const override;

	// Friended to allow access to handle functions above
	friend USGSCppV4_AttributeSet;
};
