// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Pawn.h"

#include "GenericTeamAgentInterface.h"
#include "AbilitySystemInterface.h"
#include "Abilities/SGSCppV4_AttributeSet.h"
#include "Abilities/SGSCppV4_AbilitySystemComponent.h"
#include "Components/SGSCppV4_Component_Character_Init.h"
#include "Data/SGSCppV4_Interface_GameplayAbility.h"

#include "SGSCppV4_Pawn.generated.h"


UCLASS()
class SIRGASSYSTEMRUNTIME_API ASGSCppV4_Pawn : public APawn, public IAbilitySystemInterface, public IGenericTeamAgentInterface, public ISGSCppV4_Interface_GameplayAbility
{
	GENERATED_BODY()
	
protected:
	/** The component used to handle ability system interactions */
	UPROPERTY()
	USGSCppV4_AbilitySystemComponent* AbilitySystemComponent;
	
	/** List of attributes modified by the ability system */
	UPROPERTY()
	USGSCppV4_AttributeSet* AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FSGSCpp")
	USGSCppV4_Component_Character_Init* SGSCppV4_Component_Character_Init;
	
	
public:
	
	ASGSCppV4_Pawn();
	
	UFUNCTION(BlueprintPure, Category = "FSGSCpp|Getter")
	USGSCppV4_AbilitySystemComponent* GetSGSCppAbilitySystemComponent() ;
	
	// Implement IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	virtual void OnRep_Controller() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "SGSCppV4|InterfaceFunction")
	USGSCppV4_Component_Character_Init* SGSCppV4_Bfl_GetGameplayAbility_Implementation() const;

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
	void FSGSCppOnDamaged(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ASGSCppV4_Pawn* InstigatorCharacter, AActor* DamageCauser);

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
	
	/** Returns maximum health, health will never be greater than this */
	UFUNCTION(BlueprintCallable, Category = "FSGSCpp|Getter")
	virtual float FSGSCppGetMaxHealth() const;

	/** Returns current mana */
	UFUNCTION(BlueprintCallable, Category = "FSGSCpp|Getter")
	virtual float FSGSCppGetMana() const;

	/** Returns maximum mana, mana will never be greater than this */
	UFUNCTION(BlueprintCallable, Category = "FSGSCpp|Getter")
	virtual float FSGSCppGetMaxMana() const;

	/** Returns current movement speed */
	UFUNCTION(BlueprintCallable, Category = "FSGSCpp|Getter")
	virtual float FSGSCppGetMoveSpeed() const;

	/** Returns the character level that is passed to the ability system */
	UFUNCTION(BlueprintCallable, Category = "FSGSCpp|Getter")
	virtual int32 FSGSCppGetCharacterLevel() const;
	
	UFUNCTION(BlueprintCallable, Category = "FSGSCpp|Getter")
	virtual float FSGSCppGetHealth() const;

	UFUNCTION(BlueprintPure, Category = "FSGSCpp|Getter")
	virtual bool FSGSCppGetIsAlive();

	/**
	* Данные Setter
	*/

	UFUNCTION(BlueprintCallable, Category = "FSGSCpp|Setter")
	void FSGSCppSetHealth(float SetNewHealth);

protected:

	// Called from RPGAttributeSet, these call BP events above
	virtual void HandleDamage(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ASGSCppV4_Pawn* InstigatorCharacter, AActor* DamageCauser);
	virtual void HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	virtual void HandleManaChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	virtual void HandleMoveSpeedChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	/** Required to support AIPerceptionSystem */
	virtual FGenericTeamId GetGenericTeamId() const override;

	// Friended to allow access to handle functions above
	friend USGSCppV4_AttributeSet;
};
