// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.



#include "Abilities/SGSCppV4_AttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Abilities/SGSCppV4_AbilitySystemComponent.h"
#include "Game/SGSCppV4_Character.h"


USGSCppV4_AttributeSet::USGSCppV4_AttributeSet()
	: Health(1.f)
	, MaxHealth(1.f)
	, Mana(0.f)
	, MaxMana(0.f)
	, AttackPower(1.0f)
	, DefensePower(1.0f)
	, MoveSpeed(1.0f)
	, Damage(0.0f)
	, ExperienceCur(0.0f)
	, ExperienceMax(1.0f)
{
}

void USGSCppV4_AttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	// This is called whenever attributes change, so for max health/mana we want to scale the current totals to match
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
	else if (Attribute == GetMaxManaAttribute())
	{
		AdjustAttributeForMaxChange(Mana, MaxMana, NewValue, GetManaAttribute());
	}
	else if (Attribute == GetMaxStaminaAttribute())
	{
		AdjustAttributeForMaxChange(Stamina, MaxStamina, NewValue, GetStaminaAttribute());
	}
}

void USGSCppV4_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USGSCppV4_AttributeSet, Health);
	DOREPLIFETIME(USGSCppV4_AttributeSet, MaxHealth);
	DOREPLIFETIME(USGSCppV4_AttributeSet, Mana);
	DOREPLIFETIME(USGSCppV4_AttributeSet, MaxMana);
	DOREPLIFETIME(USGSCppV4_AttributeSet, Stamina);
	DOREPLIFETIME(USGSCppV4_AttributeSet, MaxStamina);
	DOREPLIFETIME(USGSCppV4_AttributeSet, AttackPower);
	DOREPLIFETIME(USGSCppV4_AttributeSet, DefensePower);
	DOREPLIFETIME(USGSCppV4_AttributeSet, MoveSpeed);
	DOREPLIFETIME(USGSCppV4_AttributeSet, ExperienceCur);
	DOREPLIFETIME(USGSCppV4_AttributeSet, ExperienceMax);
}

void USGSCppV4_AttributeSet::SetHpAndMaxHp(float NewHpCurLocal, float NewHpMaxLocal)
{
	SetMaxHealth(NewHpMaxLocal);
	OnRep_MaxHealth(NewHpMaxLocal);
	
	float InHpLocal = FMath::Clamp(NewHpCurLocal, 0.0f, GetMaxHealth());
	SetHealth(InHpLocal);
	OnRep_Health(InHpLocal);
}

void USGSCppV4_AttributeSet::AdjustAttributeForMaxChange(
	FGameplayAttributeData& AffectedAttribute,
	const FGameplayAttributeData& MaxAttribute,
	float NewMaxValue,
	const FGameplayAttribute& AffectedAttributeProperty
	)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// Change current value to maintain the current Val / Max percent
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

void USGSCppV4_AttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USGSCppV4_AttributeSet, Health, OldValue);
}

void USGSCppV4_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USGSCppV4_AttributeSet, MaxHealth, OldValue);
}

void USGSCppV4_AttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USGSCppV4_AttributeSet, Mana, OldValue);
}

void USGSCppV4_AttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USGSCppV4_AttributeSet, MaxMana, OldValue);
}

void USGSCppV4_AttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USGSCppV4_AttributeSet, Stamina, OldValue);
}

void USGSCppV4_AttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USGSCppV4_AttributeSet, MaxStamina, OldValue);
}

void USGSCppV4_AttributeSet::OnRep_AttackPower(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USGSCppV4_AttributeSet, AttackPower, OldValue);
}

void USGSCppV4_AttributeSet::OnRep_DefensePower(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USGSCppV4_AttributeSet, DefensePower, OldValue);
}

void USGSCppV4_AttributeSet::OnRep_MoveSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USGSCppV4_AttributeSet, MoveSpeed, OldValue);
}

void USGSCppV4_AttributeSet::OnRep_ExperienceCur(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USGSCppV4_AttributeSet, ExperienceCur, OldValue);
}

void USGSCppV4_AttributeSet::OnRep_ExperienceMax(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USGSCppV4_AttributeSet, ExperienceMax, OldValue);
}

void USGSCppV4_AttributeSet::OnRep_Water(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USGSCppV4_AttributeSet, Water, OldValue);
}

void USGSCppV4_AttributeSet::OnRep_MaxWater(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USGSCppV4_AttributeSet, MaxWater, OldValue);
}

void USGSCppV4_AttributeSet::OnRep_Food(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USGSCppV4_AttributeSet, Food, OldValue);
}

void USGSCppV4_AttributeSet::OnRep_MaxFood(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USGSCppV4_AttributeSet, MaxFood, OldValue);
}

void USGSCppV4_AttributeSet::OnRep_Oxygen(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USGSCppV4_AttributeSet, Oxygen, OldValue);
}

void USGSCppV4_AttributeSet::OnRep_MaxOxygen(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USGSCppV4_AttributeSet, MaxOxygen, OldValue);
}

void USGSCppV4_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	// Compute the delta between old and new, if it is available
	float DeltaValue = 0;
	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	{
		// If this was additive, store the raw delta value to be passed along later
		DeltaValue = Data.EvaluatedData.Magnitude;
	}

	// Get the Target actor, which should be our owner
	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	ASGSCppV4_Character* TargetCharacter = nullptr;
	
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<ASGSCppV4_Character>(TargetActor);
	}

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		// Get the Source actor
		AActor* SourceActor = nullptr;
		AController* SourceController = nullptr;
		ASGSCppV4_Character* SourceCharacter = nullptr;

		if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
		{
			SourceActor = Source->AbilityActorInfo->AvatarActor.Get();
			SourceController = Source->AbilityActorInfo->PlayerController.Get();

			if (SourceController == nullptr && SourceActor != nullptr)
			{
				if (APawn* Pawn = Cast<APawn>(SourceActor))
				{
					SourceController = Pawn->GetController();
				}
			}

			// Use the controller to find the source pawn
			if (SourceController)
			{
				SourceCharacter = Cast<ASGSCppV4_Character>(SourceController->GetPawn());
			}
			else
			{
				SourceCharacter = Cast<ASGSCppV4_Character>(SourceActor);
			}

			// Set the causer actor based on context if it's set
			if (Context.GetEffectCauser())
			{
				SourceActor = Context.GetEffectCauser();
			}
		}

		// Try to extract a hit result
		FHitResult HitResult;

		if (Context.GetHitResult())
		{
			HitResult = *Context.GetHitResult();
		}

		// Store a local copy of the amount of damage done and clear the damage attribute
		const float LocalDamageDone = GetDamage();
		SetDamage(0.f);

		if (LocalDamageDone > 0)
		{
			// Apply the health change and then clamp it
			const float OldHealth = GetHealth();
			SetHealth(FMath::Clamp(OldHealth - LocalDamageDone, 0.0f, GetMaxHealth()));

			if (TargetCharacter)
			{
				// This is proper damage
				TargetCharacter->HandleDamage(LocalDamageDone, HitResult, SourceTags, SourceCharacter, SourceActor);

				// Call for all health changes
				TargetCharacter->HandleHealthChanged(-LocalDamageDone, SourceTags);
			}
		}
	}
	else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Handle other health changes such as from healing or direct modifiers
		// First clamp it
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

		if (TargetCharacter)
		{
			// Call for all health changes
			TargetCharacter->HandleHealthChanged(DeltaValue, SourceTags);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		// Clamp mana
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));

		if (TargetCharacter)
		{
			// Call for all mana changes
			TargetCharacter->HandleManaChanged(DeltaValue, SourceTags);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetMoveSpeedAttribute())
	{
		if (TargetCharacter)
		{
			// Call for all movespeed changes
			TargetCharacter->HandleMoveSpeedChanged(DeltaValue, SourceTags);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		// Clamp Stamina
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));

		if (TargetCharacter)
		{
			// Call for all mana changes
			TargetCharacter->HandleStaminaChanged(DeltaValue, SourceTags);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetWaterAttribute())
	{
		// Clamp Stamina
		SetWater(FMath::Clamp(GetWater(), 0.0f, GetMaxWater()));

		if (TargetCharacter)
		{
			// Call for all mana changes
			TargetCharacter->HandleStaminaChanged(DeltaValue, SourceTags);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetFoodAttribute())
	{
		// Clamp Stamina
		SetFood(FMath::Clamp(GetFood(), 0.0f, GetMaxFood()));

		if (TargetCharacter)
		{
			// Call for all mana changes
			TargetCharacter->HandleStaminaChanged(DeltaValue, SourceTags);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetOxygenAttribute())
	{
		// Clamp Stamina
		SetOxygen(FMath::Clamp(GetOxygen(), 0.0f, GetMaxOxygen()));

		if (TargetCharacter)
		{
			// Call for all mana changes
			TargetCharacter->HandleOxygenChanged(DeltaValue, SourceTags);
		}
	}
}
