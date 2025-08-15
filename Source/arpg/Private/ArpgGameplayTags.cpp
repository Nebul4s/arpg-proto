// Fill out your copyright notice in the Description page of Project Settings.



#include "ArpgGameplayTags.h"
#include "GameplayTagsManager.h"

FArpgGameplayTags FArpgGameplayTags::GameplayTags;

void FArpgGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"));
	GameplayTags.Attributes_Primary_Dexterity = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Dexterity"));
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"));
	
	GameplayTags.Attributes_Secondary_MaxLife = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxLife"));
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"));
	
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"));
	GameplayTags.Attributes_Secondary_Evasion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Evasion"));
	GameplayTags.Attributes_Secondary_EnergyShield = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.EnergyShield"));
	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"));
	GameplayTags.Attributes_Secondary_MovementSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MovementSpeed"));
	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"));
	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"));
	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"));
	GameplayTags.Attributes_Secondary_CriticalHitMultiplier = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitMultiplier"));
	GameplayTags.Attributes_Secondary_AccuracyRating = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.AccuracyRating"));
	GameplayTags.Attributes_Secondary_AttackSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.AttackSpeed"));
	GameplayTags.Attributes_Secondary_CastSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CastSpeed"));


	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"));
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"));
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"));
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"));

	/*
	 * Damage types
	 */
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"));
	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Fire"));
	GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Lightning"));
	GameplayTags.Damage_Cold = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Cold"));
	GameplayTags.Damage_Noxious = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Noxious"));
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Physical"));
	
	/*
	 * Resistances
	 */
	GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Fire"));
	GameplayTags.Attributes_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Lightning"));
	GameplayTags.Attributes_Resistance_Cold = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Cold"));
	GameplayTags.Attributes_Resistance_Noxious = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Noxious"));
	GameplayTags.Attributes_Resistance_AdditionalPhysicalDamageReduction = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.AdditionalPhysicalDamageReduction"));

	/*
	 * map of damage types to res
	 */

	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire, GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lightning, GameplayTags.Attributes_Resistance_Lightning);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Cold, GameplayTags.Attributes_Resistance_Cold);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Noxious, GameplayTags.Attributes_Resistance_Noxious);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical, GameplayTags.Attributes_Resistance_AdditionalPhysicalDamageReduction);

	/*
	 * effects
	 */
	
	GameplayTags.Stun = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Stun"));

	
}
