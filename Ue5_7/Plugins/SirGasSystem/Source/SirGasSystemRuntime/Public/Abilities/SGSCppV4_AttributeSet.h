// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "Net/UnrealNetwork.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "SGSCppV4_AttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


/**
 * 
 */
UCLASS()
class SIRGASSYSTEMRUNTIME_API USGSCppV4_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:

	// Constructor and overrides
	USGSCppV4_AttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Current Health, when 0 we expect owner to die. Capped by MaxHealth */
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(USGSCppV4_AttributeSet, Health)

	/** MaxHealth is its own attribute, since GameplayEffects may modify it */
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(USGSCppV4_AttributeSet, MaxHealth)

	/** Current Mana, used to execute special abilities. Capped by MaxMana */
	UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing=OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(USGSCppV4_AttributeSet, Mana)

	/** MaxMana is its own attribute, since GameplayEffects may modify it */
	UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing=OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(USGSCppV4_AttributeSet, MaxMana)

	/** Current Mana, used to execute special abilities. Capped by MaxMana */
	UPROPERTY(BlueprintReadOnly, Category = "Stamina", ReplicatedUsing=OnRep_Stamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(USGSCppV4_AttributeSet, Stamina)

	/** MaxMana is its own attribute, since GameplayEffects may modify it */
	UPROPERTY(BlueprintReadOnly, Category = "Stamina", ReplicatedUsing=OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(USGSCppV4_AttributeSet, MaxStamina)
	
	/** AttackPower of the attacker is multiplied by the base Damage to reduce health, so 1.0 means no bonus */
	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_AttackPower)
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(USGSCppV4_AttributeSet, AttackPower)

	/** Base Damage is divided by DefensePower to get actual damage done, so 1.0 means no bonus */
	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_DefensePower)
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(USGSCppV4_AttributeSet, DefensePower)

	/** MoveSpeed affects how fast characters can move */
	UPROPERTY(BlueprintReadOnly, Category = "MoveSpeed", ReplicatedUsing = OnRep_MoveSpeed)
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(USGSCppV4_AttributeSet, MoveSpeed)

	/** Damage is a 'temporary' attribute used by the DamageExecution to calculate final damage, which then turns into -Health */
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(USGSCppV4_AttributeSet, Damage)

	/** Damage is a 'temporary' attribute used by the DamageExecution to calculate final damage, which then turns into -Health */
	UPROPERTY(BlueprintReadOnly, Category = "Experience")
	FGameplayAttributeData ExperienceCur;
	ATTRIBUTE_ACCESSORS(USGSCppV4_AttributeSet, ExperienceCur)
		
	/** Damage is a 'temporary' attribute used by the DamageExecution to calculate final damage, which then turns into -Health */
	UPROPERTY(BlueprintReadOnly, Category = "Experience")
	FGameplayAttributeData ExperienceMax;
	ATTRIBUTE_ACCESSORS(USGSCppV4_AttributeSet, ExperienceMax)

	/** Water */
	UPROPERTY(BlueprintReadOnly, Category = "Water", ReplicatedUsing=OnRep_Water)
	FGameplayAttributeData Water;
	ATTRIBUTE_ACCESSORS(USGSCppV4_AttributeSet, Water)

	UPROPERTY(BlueprintReadOnly, Category = "Water", ReplicatedUsing=OnRep_MaxWater)
	FGameplayAttributeData MaxWater;
	ATTRIBUTE_ACCESSORS(USGSCppV4_AttributeSet, MaxWater)

	/** Food */
	UPROPERTY(BlueprintReadOnly, Category = "Food", ReplicatedUsing=OnRep_Food)
	FGameplayAttributeData Food;
	ATTRIBUTE_ACCESSORS(USGSCppV4_AttributeSet, Food)

	UPROPERTY(BlueprintReadOnly, Category = "Food", ReplicatedUsing=OnRep_MaxFood)
	FGameplayAttributeData MaxFood;
	ATTRIBUTE_ACCESSORS(USGSCppV4_AttributeSet, MaxFood)
	
	/** Oxygen */
	UPROPERTY(BlueprintReadOnly, Category = "Oxygen", ReplicatedUsing=OnRep_Oxygen)
	FGameplayAttributeData Oxygen;
	ATTRIBUTE_ACCESSORS(USGSCppV4_AttributeSet, Oxygen)

	UPROPERTY(BlueprintReadOnly, Category = "Oxygen", ReplicatedUsing=OnRep_MaxOxygen)
	FGameplayAttributeData MaxOxygen;
	ATTRIBUTE_ACCESSORS(USGSCppV4_AttributeSet, MaxOxygen)

	/** Attr */
	UFUNCTION(BlueprintCallable, Category = "Attr")
	void SetHpAndMaxHp(float NewHpCurLocal, float NewHpMaxLocal);

protected:
	/** Helper function to proportionally adjust the value of an attribute when it's associated max attribute changes. (i.e. When MaxHealth increases, Health increases by an amount that maintains the same percentage as before) */
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

	// These OnRep functions exist to make sure that the ability system internal representations are synchronized properly during replication
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_AttackPower(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_DefensePower(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MoveSpeed(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_ExperienceCur(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_ExperienceMax(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Water(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxWater(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Food(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxFood(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	virtual void OnRep_Oxygen(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxOxygen(const FGameplayAttributeData& OldValue);

};
