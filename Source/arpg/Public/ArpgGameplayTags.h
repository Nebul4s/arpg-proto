// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 
 */

struct FArpgGameplayTags
{
public:
	static const FArpgGameplayTags& Get() {return GameplayTags;};
	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Dexterity;
	FGameplayTag Attributes_Primary_Intelligence;
	
	FGameplayTag Attributes_Secondary_MaxLife;
	FGameplayTag Attributes_Secondary_MaxMana;
	
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_Evasion;
	FGameplayTag Attributes_Secondary_EnergyShield;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_MovementSpeed;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitMultiplier;
	FGameplayTag Attributes_Secondary_AccuracyRating;
	FGameplayTag Attributes_Secondary_AttackSpeed;
	FGameplayTag Attributes_Secondary_CastSpeed;
	
protected:
	
private:
	static FArpgGameplayTags GameplayTags;
};