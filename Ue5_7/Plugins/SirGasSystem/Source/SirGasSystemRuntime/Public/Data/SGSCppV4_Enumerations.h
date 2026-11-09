// Copyright (c) 2026 SirotkinAleksandr. All Rights Reserved.

#pragma once


UENUM(BlueprintType)
enum class ESGSSirDirectionMovement : uint8
{
	None_None,
	Forward_None, 
	Forward_Right,
	Forward_Left,
	Back_None,
	Back_Left,
	Back_Right,
	None_Right,
	None_Left,
};
UENUM(BlueprintType)
enum class ESGSSirHitReactDirection : uint8
{
	// 0
	None			UMETA(DisplayName = "None"),
	// 1
	Left 			UMETA(DisplayName = "Left"),
	// 2
	Front 			UMETA(DisplayName = "Front"),
	// 3
	Right			UMETA(DisplayName = "Right"),
	// 4
	Back			UMETA(DisplayName = "Back")
};


UENUM(BlueprintType)
enum class ESGSSirTypeInvItem : uint8
{
	Default,
	Weapon, 
	Spell,
	Bow,
	Torch,
	Potion,
	Food,
	Resource,
	Quest,
	Craft,
	Magic,
	Ball,
	WeaponProjectile,
	Artefact,
	Block
};