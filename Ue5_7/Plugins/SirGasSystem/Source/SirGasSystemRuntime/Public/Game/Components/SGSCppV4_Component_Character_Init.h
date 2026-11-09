// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once

#include "Abilities/GameplayAbility.h"

#include "Abilities/SGSCppV4_AbilitySystemComponent.h"
#include "Components/ActorComponent.h"
#include "DataAssets/SGSCppV4_DataAsset_Character_Init.h"
#include "SGSCppV4_Component_Character_Init.generated.h"

/*
 * Данный компонент, требуется, для возможности создания раззных классов.
 * Pawn and Character и через данный компонент уже инициализровать
 * нужные данные в персонаже.
 */

/*
* This component is required to enable the creation of various classes—
* such as Pawn and Character—and to subsequently initialize the
* necessary data within the character via this component. 
*/

class ASGSCppV4_Character;
class ASGSCppV4_Pawn;

UCLASS(ClassGroup=("FSGSCpp|InventarySystemV4"), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType, meta = (ShowWorldContextPin))
class SIRGASSYSTEMRUNTIME_API USGSCppV4_Component_Character_Init : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USGSCppV4_Component_Character_Init();

protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	
	UPROPERTY()
	UAbilitySystemComponent * ASC ;
	
	UPROPERTY()
	USGSCppV4_AttributeSet* AttributeSet;

	UPROPERTY()
	TArray<UGameplayAbility * > V4_ArrActiveAbilities;
	
	UPROPERTY()
	TArray<TSubclassOf<UGameplayAbility>> V4_GameplayAbilityClasses;

	UPROPERTY()
	bool bAbilitiesInitialized;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FSGSCpp|Character", meta = (ClampMin=1, Min=1))
	int32 CharacterLevel;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FSGSCpp")
	USGSCppV4_DataAsset_Attr_Character_Init* SGSCppV4_DataAssetInit;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,  FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "FSGSCpp|Setter")
	void FSGSCppSetCharacterLevel(int32 NewLevel);
	
	/**
	* Character Attrubite
	*/

	//UFUNCTION(BlueprintCallable, Category = "FSGSCpp|Attr|Initialization")
	UFUNCTION()
	void FSGSCppInitializationCharacterAttrubite(USGSCppV4_AbilitySystemComponent* AbilitySystemComponent, USGSCppV4_AttributeSet* SGSCppV4_AttributeSet) ;

	// Implement IAbilitySystemInterface
	USGSCppV4_AbilitySystemComponent* GetAbilitySystemComponent() ;

	// GameplayAbility
	UFUNCTION(BlueprintCallable, Category = "FSGSCpp|Abilities|Add")
	bool FSGSCppAddNewGameplayAbility(TSubclassOf<UGameplayAbility> NewGameplayAbility);
	
	UFUNCTION(BlueprintCallable, Category = "FSGSCpp|Abilities|Add")
	void FSGSCppAddArrNewGameplayAbility(TArray<TSubclassOf<UGameplayAbility>> NewArrGameplayAbilities);

	// GameplayEffect
	UFUNCTION(BlueprintCallable, Category = "FSGSCpp|GameplayEffect|Add")
	virtual void FSGSCppAddGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffectL);
	
	UFUNCTION(BlueprintCallable, Category = "FSGSCpp|GameplayEffect|Add")
	virtual void FSGSCppAddGameplayEffects(TArray<TSubclassOf<UGameplayEffect>> GameplayEffectsL );

	/**
	* Cancel
	*/
	
	UFUNCTION(BlueprintCallable, Category = "FSGSCpp|Abilities|Cancel")
	void FSGSCppCancelAbility(FGameplayTag AbilityTag);

	/**
	* Has
	*/
	
	UFUNCTION(BlueprintPure, Category = "FSGSCpp|Abilities|Has")
	void FSGSCppCheckTag(FGameplayTagContainer AbilityTags, bool& TagIsEmpty);
	
protected:
	
	/** Apply the startup gameplay abilities and effects */
	void AddStartupGameplayAbilities();

	/** Adds slotted item abilities if needed */
	void AddGameplayAbilities();
	
	/** Attempts to remove any startup gameplay abilities */
	void RemoveStartupGameplayAbilities();
		
	/**
	* ЛОГИКА С ТЕГАМИ
	*/

	UFUNCTION(BlueprintCallable, Category = "FSGSCpp|Abilities|Activate", meta = (Keywords = "FSGSCppV4 Activate Abilities With Tags"))
	bool FSGSCppActivateAbilitiesWithTags(FGameplayTagContainer AbilityTags, bool bAllowRemoteActivation = true);

	UFUNCTION(BlueprintCallable, Category = "FSGSCpp|Abilities|Activate", meta = (Keywords = "FSGSCppV4 Activate Ability With Tag"))
	bool FSGSCppActivateAbilityWithTag(FGameplayTag AbilityTagL, bool bAllowRemoteActivation = true);

	/**
	* Abilities - Getter
	*/

	UFUNCTION(BlueprintCallable, Category = "FSGSCpp|Abilities|Gettter", meta = (Keywords = "FSGSCppV4 Get Active Abilities With Tags"))
	void FSGSCppGetActiveAbilitiesWithTags(FGameplayTagContainer AbilityTags, TArray<UGameplayAbility*> &ActiveAbilities);
	
	UFUNCTION(BlueprintCallable, Category = "FSGSCpp|Abilities|Gettter", meta = (Keywords = "FSGSCppV4 Get Cooldown Remaining For Tag"))
	bool FSGSCppGetCooldownRemainingForTag(FGameplayTagContainer CooldownTags, float& TimeRemaining, float& CooldownDuration);

	UFUNCTION(BlueprintCallable, Category = "FSGSCpp|Getter", meta = (Keywords = "FSGSCppV4 Get Character Attr"))
	void FSGSCppV4_GetCharacterAttr(float &AttackPower, float &DefensePower, float &MoveSpeed, float &Damage);

	UFUNCTION(BlueprintPure, Category = "FSGSCpp|Getter", meta = (Keywords = "FSGSCppV4 Get Health | HP"))
	void FSGSCppV4_GetHealth(float &Health, float &HealthMax, float &Percent);

	UFUNCTION(BlueprintPure, Category = "FSGSCpp|Getter", meta = (Keywords = "FSGSCppV4 Get Stamina | SP"))
	void FSGSCppV4_GetStamina(float &Stamina, float &StaminaMax, float &Percent);

	UFUNCTION(BlueprintCallable, Category = "FSGSCpp|Getter", meta = (Keywords = "FSGSCppV4 Get Mana | MP"))
	void FSGSCppV4_Mana(float &Mana, float &ManaMax, float &Percent);

	UFUNCTION(BlueprintPure, Category = "FSGSCpp|Getter", meta = (Keywords = "FSGSCppV4 Get Experience | XP"))
	void FSGSCppV4_GetExperience(float &Experience, float &ExperienceMax, float &Percent);

	UFUNCTION(BlueprintPure, Category = "FSGSCpp|Getter", meta = (Keywords = "FSGSCppV4 Get Water | "))
	void FSGSCppV4_GetWater(float &Water, float &WaterMax, float &Percent);

	UFUNCTION(BlueprintPure, Category = "FSGSCpp|Getter", meta = (Keywords = "FSGSCppV4 Get Food | "))
	void FSGSCppV4_GetFood(float &Food, float &FoodMax, float &Percent);

	UFUNCTION(BlueprintPure, Category = "FSGSCpp|Getter", meta = (Keywords = "FSGSCppV4 Get Oxygen | "))
	void FSGSCppV4_GetOxygen(float &Oxygen, float &OxygenMax, float &Percent);

	/**
	* Данные Setter
	*/

	UFUNCTION(BlueprintCallable, Category = "FSGSCpp|Setter")
	void FSGSCppSetHealth(float SetNewHealth);

};
