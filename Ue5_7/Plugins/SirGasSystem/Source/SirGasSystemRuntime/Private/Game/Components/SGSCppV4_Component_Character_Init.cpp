// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#include "Game/Components/SGSCppV4_Component_Character_Init.h"
#include "Abilities/SGSCppV4_GameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemLog.h"
#include "Abilities/SGSCppV4_AttributeSet.h"


//#include "Game/SGSCppCharacterV4.h"
//#include "Game/SGSCppPawnV4.h"


// Sets default values for this component's properties
USGSCppV4_Component_Character_Init::USGSCppV4_Component_Character_Init()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USGSCppV4_Component_Character_Init::BeginPlay()
{
	Super::BeginPlay();
	
	/*
	CustomPawn = Cast<ASGSCppPawnV4>(GetOwner());	
	if (IsValid(CustomPawn)) ASC = Cast<USGSCppAbilitySystemComponent>(CustomPawn->GetSGSCppAbilitySystemComponent());
	else
	{
		CustomCharacter = Cast<ASGSCppCharacterV4>(GetOwner());	
		if (IsValid(CustomCharacter)) ASC = Cast<USGSCppAbilitySystemComponent>(CustomCharacter->GetSGSCppAbilitySystemComponent());
	}
	
	if (IsValid(ASC))
	{
		GetAbilitySystemComponent()->InitAbilityActorInfo(GetOwner(), GetOwner());
		FSGSCppInitializationCharacterAttrubite();
	}
	*/
	
}

void USGSCppV4_Component_Character_Init::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}


// Called every frame
void USGSCppV4_Component_Character_Init::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USGSCppV4_Component_Character_Init::FSGSCppSetCharacterLevel(int32 NewLevel)
{
	if (CharacterLevel != NewLevel && NewLevel > 0)
	{
		CharacterLevel = NewLevel;
		
		RemoveStartupGameplayAbilities();
		AddStartupGameplayAbilities();
	}
}

void USGSCppV4_Component_Character_Init::FSGSCppInitializationCharacterAttrubite(USGSCppV4_AbilitySystemComponent * AbilitySystemComponent, USGSCppV4_AttributeSet* SGSCppV4_AttributeSet)
{
	if (!bAbilitiesInitialized)
	{
		if (!IsValid(AbilitySystemComponent))
		{
			ABILITY_LOG(Warning, TEXT("Is NOT Valid - AbilitySystemComponent"));
			return;
		}
		
		ASC = AbilitySystemComponent;
		AttributeSet = SGSCppV4_AttributeSet;
		
		GetAbilitySystemComponent()->InitAbilityActorInfo(GetOwner(), GetOwner());

		if (IsValid(SGSCppV4_DataAssetInit)) FSGSCppAddArrNewGameplayAbility(SGSCppV4_DataAssetInit->GameplayAbilities);
		
		if (IsValid(SGSCppV4_DataAssetInit)) FSGSCppAddGameplayEffects(SGSCppV4_DataAssetInit->GameplayEffects);

		GetAbilitySystemComponent()->RefreshAbilityActorInfo();
		
		bAbilitiesInitialized = true;
	}
}

USGSCppV4_AbilitySystemComponent* USGSCppV4_Component_Character_Init::GetAbilitySystemComponent() 
{
	return Cast<USGSCppV4_AbilitySystemComponent>(ASC);
}

/**
* Add GameplayAbility
*/
		
bool USGSCppV4_Component_Character_Init::FSGSCppAddNewGameplayAbility(TSubclassOf<UGameplayAbility> NewGameplayAbility)
{
	if (IsValid(GetAbilitySystemComponent()))
	{
		GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(NewGameplayAbility, CharacterLevel, INDEX_NONE, this));
		UGameplayAbility* AbilityInstance = NewGameplayAbility.Get()->GetDefaultObject<UGameplayAbility>();

		V4_ArrActiveAbilities.Add(AbilityInstance);
		
		return true;	
	}
	return false;
}

void USGSCppV4_Component_Character_Init::FSGSCppAddArrNewGameplayAbility(TArray<TSubclassOf<UGameplayAbility>> NewArrGameplayAbilities)
{
	for (TSubclassOf<UGameplayAbility> i : NewArrGameplayAbilities)
	{
		FSGSCppAddNewGameplayAbility(i);
	}
}

/**
* Add GameplayEffect
*/

void USGSCppV4_Component_Character_Init::FSGSCppAddGameplayEffects(TArray<TSubclassOf<UGameplayEffect>> GameplayEffectsL)
{
	for (TSubclassOf<UGameplayEffect> GameplayEffect : GameplayEffectsL)
	{
		FSGSCppAddGameplayEffect(GameplayEffect);
	}
}
	
void USGSCppV4_Component_Character_Init::FSGSCppAddGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffectL)
{
	FGameplayEffectContextHandle EffectContext = GetAbilitySystemComponent()->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectL, CharacterLevel, EffectContext);
	if (NewHandle.IsValid())
	{
		GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(),  GetAbilitySystemComponent());
	}
}


void USGSCppV4_Component_Character_Init::FSGSCppCancelAbility(FGameplayTag AbilityTag)
{
	if (GetAbilitySystemComponent())
	{
		FGameplayTagContainer GameplayTagContainer;
		GameplayTagContainer.AddTag(AbilityTag);

		GetAbilitySystemComponent()->CancelAbilities(&GameplayTagContainer, nullptr, nullptr);
	}
}

void USGSCppV4_Component_Character_Init::FSGSCppCheckTag(FGameplayTagContainer AbilityTags, bool& TagIsEmpty)
{
	TArray<UGameplayAbility*> GetActiveAbilitiesLocal;
	
	FSGSCppGetActiveAbilitiesWithTags(AbilityTags, GetActiveAbilitiesLocal);
	
	TagIsEmpty = GetActiveAbilitiesLocal.IsEmpty();
}

void USGSCppV4_Component_Character_Init::AddStartupGameplayAbilities()
{
	check(GetAbilitySystemComponent());
	if (!IsValid(SGSCppV4_DataAssetInit)) return;
	
	if (GetOwner()->GetLocalRole() == ROLE_Authority && !bAbilitiesInitialized)
	{
		// Grant abilities, but only on the server	
		for (TSubclassOf<UGameplayAbility>& StartupAbility : SGSCppV4_DataAssetInit->GameplayAbilities)
		{
			//GetAbilitySystemComponent()->GiveAbility(FGameplayAbilitySpec(StartupAbility, CharacterLevel, INDEX_NONE, this));
			
			FSGSCppAddNewGameplayAbility(StartupAbility);
		}

		// Now apply passives
		for (TSubclassOf<UGameplayEffect>& GameplayEffect : SGSCppV4_DataAssetInit->GameplayEffects)
		{

			FGameplayEffectContextHandle EffectContext = GetAbilitySystemComponent()->MakeEffectContext();
			EffectContext.AddSourceObject(this);
			//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, TEXT("3GameplayEffects")); // print string
			FGameplayEffectSpecHandle NewHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffect, CharacterLevel, EffectContext);
			if (NewHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGEHandle = GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), GetAbilitySystemComponent());
			}
		}
		//AddGameplayAbilities();

		bAbilitiesInitialized = true;
	}
}

void USGSCppV4_Component_Character_Init::AddGameplayAbilities()
{
	for (UGameplayAbility * ActiveAbilit : V4_ArrActiveAbilities)
	{
		if (IsValid(ActiveAbilit))
		{
			// GetAbilitySystemComponent()->GiveAbility(ActiveAbilit);
			
			FSGSCppAddNewGameplayAbility(ActiveAbilit->GetClass());
		}
	}
}

void USGSCppV4_Component_Character_Init::RemoveStartupGameplayAbilities()
{
	check(GetAbilitySystemComponent());

	if (bAbilitiesInitialized)
	{
		// Remove any abilities added from a previous call
		TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;

		for (const FGameplayAbilitySpec& Spec : ASC->GetActivatableAbilities())
		{
			if (!IsValid(SGSCppV4_DataAssetInit)) return;
			
			if ((Spec.SourceObject == this) && V4_GameplayAbilityClasses.Contains(Spec.Ability->GetClass()))
			{
				AbilitiesToRemove.Add(Spec.Handle);
			}
		}

		// Do in two passes so the removal happens after we have the full list
		for (int32 i = 0; i < AbilitiesToRemove.Num(); i++)
		{
			GetAbilitySystemComponent()->ClearAbility(AbilitiesToRemove[i]);
		}

		// Remove all of the passive gameplay effects that were applied by this character
		FGameplayEffectQuery Query;
		Query.EffectSource = this;
		
		GetAbilitySystemComponent()->RemoveActiveEffects(Query);

	}
}

bool USGSCppV4_Component_Character_Init::FSGSCppActivateAbilitiesWithTags(FGameplayTagContainer AbilityTags,
                                                              bool bAllowRemoteActivation)
{
	if (GetAbilitySystemComponent())
	{
		return GetAbilitySystemComponent()->TryActivateAbilitiesByTag(AbilityTags, bAllowRemoteActivation);
	}

	return false;
}

bool USGSCppV4_Component_Character_Init::FSGSCppActivateAbilityWithTag(FGameplayTag AbilityTagL, bool bAllowRemoteActivation)
{
	if (GetAbilitySystemComponent())
	{
		FGameplayTagContainer GameplayTagContainer;
		GameplayTagContainer.AddTag(AbilityTagL);

		return GetAbilitySystemComponent()->TryActivateAbilitiesByTag(GameplayTagContainer, bAllowRemoteActivation);
	}

	return false;
}

void USGSCppV4_Component_Character_Init::FSGSCppGetActiveAbilitiesWithTags(FGameplayTagContainer AbilityTags,
                                                               TArray<UGameplayAbility*>& ActiveAbilities)
{
	if (GetAbilitySystemComponent())
	{
		GetAbilitySystemComponent()->GetActiveAbilitiesWithTags(AbilityTags, ActiveAbilities);
	}
}

bool USGSCppV4_Component_Character_Init::FSGSCppGetCooldownRemainingForTag(FGameplayTagContainer CooldownTags, float& TimeRemaining,
	float& CooldownDuration)
{
	if (GetAbilitySystemComponent() && CooldownTags.Num() > 0)
	{
		TimeRemaining = 0.f;
		CooldownDuration = 0.f;

		FGameplayEffectQuery const Query = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(CooldownTags);
		TArray< TPair<float, float> > DurationAndTimeRemaining = GetAbilitySystemComponent()->GetActiveEffectsTimeRemainingAndDuration(Query);
		if (DurationAndTimeRemaining.Num() > 0)
		{
			int32 BestIdx = 0;
			float LongestTime = DurationAndTimeRemaining[0].Key;
			for (int32 Idx = 1; Idx < DurationAndTimeRemaining.Num(); ++Idx)
			{
				if (DurationAndTimeRemaining[Idx].Key > LongestTime)
				{
					LongestTime = DurationAndTimeRemaining[Idx].Key;
					BestIdx = Idx;
				}
			}

			TimeRemaining = DurationAndTimeRemaining[BestIdx].Key;
			CooldownDuration = DurationAndTimeRemaining[BestIdx].Value;

			return true;
		}
	}
	return false;
}

void USGSCppV4_Component_Character_Init::FSGSCppV4_GetHealth(float& Health, float& HealthMax, float &Percent)
{
	Health = AttributeSet->GetHealth();
	HealthMax = AttributeSet->GetMaxHealth();
	Percent = Health / HealthMax;
}

void USGSCppV4_Component_Character_Init::FSGSCppV4_GetStamina(float& Stamina, float& StaminaMax, float &Percent)
{
	Stamina = AttributeSet->GetStamina();
	StaminaMax = AttributeSet->GetMaxStamina();
	Percent = Stamina / StaminaMax;
}

void USGSCppV4_Component_Character_Init::FSGSCppV4_Mana(float& Mana, float& ManaMax, float& Percent)
{
	Mana = AttributeSet->GetMana();
	ManaMax = AttributeSet->GetMaxMana();
	Percent = Mana / ManaMax;
}

void USGSCppV4_Component_Character_Init::FSGSCppV4_GetCharacterAttr(float& AttackPower, float& DefensePower,
	float& MoveSpeed, float& Damage)
{
	AttackPower = AttributeSet->GetAttackPower();
	DefensePower = AttributeSet->GetDefensePower();
	MoveSpeed = AttributeSet->GetMoveSpeed();
	Damage = AttributeSet->GetDamage();
}

void USGSCppV4_Component_Character_Init::FSGSCppV4_GetExperience(float& Experience, float& ExperienceMax,
	float& Percent)
{
	Experience = AttributeSet->GetExperienceCur();
	ExperienceMax = AttributeSet->GetExperienceMax();
	Percent = Experience / ExperienceMax;
}

void USGSCppV4_Component_Character_Init::FSGSCppV4_GetWater(float& Water, float& WaterMax, float& Percent)
{
	Water = AttributeSet->GetWater();
	WaterMax = AttributeSet->GetMaxWater();
	Percent = Water / WaterMax;
}

void USGSCppV4_Component_Character_Init::FSGSCppV4_GetFood(float& Food, float& FoodMax, float& Percent)
{
	Food = AttributeSet->GetFood();
	FoodMax = AttributeSet->GetMaxFood();
	Percent = Food / FoodMax;
}

void USGSCppV4_Component_Character_Init::FSGSCppV4_GetOxygen(float& Oxygen, float& OxygenMax, float& Percent)
{
	Oxygen = AttributeSet->GetOxygen();
	OxygenMax = AttributeSet->GetMaxOxygen();
	Percent = Oxygen / OxygenMax;
}


void USGSCppV4_Component_Character_Init::FSGSCppSetHealth(float SetNewHealth)
{
	if (AttributeSet)
	{
		AttributeSet->SetHpAndMaxHp(SetNewHealth, AttributeSet->GetMaxHealth());
	}
}


//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, TEXT("0")); // print string
//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, TEXT("1")); // print string
//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Blue, TEXT("PossessedBy")); // print string
// GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Blue, TEXT("PossessedBy")); // print string