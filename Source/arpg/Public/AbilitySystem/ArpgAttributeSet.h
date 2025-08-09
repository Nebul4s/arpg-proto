// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"   
#include "ArpgAttributeSet.generated.h"


USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties() {};

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
	
};

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class ARPG_API UArpgAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UArpgAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;


	/*
	 *Primary Attributes Start
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Strength, Category="Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UArpgAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Dexterity, Category="Primary Attributes")
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UArpgAttributeSet, Dexterity);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Intelligence, Category="Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UArpgAttributeSet, Intelligence);

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	UFUNCTION()
	void OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	/*
	 *Primary Attributes End
	*/

	/*
	 *Secondary Attributes Start
	*/

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Armor, Category="Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UArpgAttributeSet, Armor);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Evasion, Category="Secondary Attributes")
	FGameplayAttributeData Evasion;
	ATTRIBUTE_ACCESSORS(UArpgAttributeSet, Evasion);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_EnergyShield, Category="Secondary Attributes")
	FGameplayAttributeData EnergyShield;
	ATTRIBUTE_ACCESSORS(UArpgAttributeSet, EnergyShield);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_BlockChance, Category="Secondary Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UArpgAttributeSet, BlockChance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MovementSpeed, Category="Secondary Attributes")
	FGameplayAttributeData MovementSpeed;
	ATTRIBUTE_ACCESSORS(UArpgAttributeSet, MovementSpeed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_HealthRegeneration, Category="Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UArpgAttributeSet, HealthRegeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ManaRegeneration, Category="Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UArpgAttributeSet, ManaRegeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CriticalHitChance, Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UArpgAttributeSet, CriticalHitChance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CriticalHitMultiplier, Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitMultiplier;
	ATTRIBUTE_ACCESSORS(UArpgAttributeSet, CriticalHitMultiplier);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_AccuracyRating, Category="Secondary Attributes")
	FGameplayAttributeData AccuracyRating;
	ATTRIBUTE_ACCESSORS(UArpgAttributeSet, AccuracyRating);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_AttackSpeed, Category="Secondary Attributes")
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UArpgAttributeSet, AttackSpeed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CastSpeed, Category="Secondary Attributes")
	FGameplayAttributeData CastSpeed;
	ATTRIBUTE_ACCESSORS(UArpgAttributeSet, CastSpeed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxMana, Category="Secondary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UArpgAttributeSet, MaxMana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxLife, Category="Secondary Attributes")
	FGameplayAttributeData MaxLife;
	ATTRIBUTE_ACCESSORS(UArpgAttributeSet, MaxLife);
	
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
	UFUNCTION()
	void OnRep_Evasion(const FGameplayAttributeData& OldEvasion) const;
	UFUNCTION()
	void OnRep_EnergyShield(const FGameplayAttributeData& OldEnergyShield) const;
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;
	UFUNCTION()
	void OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed) const;
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;
	UFUNCTION()
	void OnRep_CriticalHitMultiplier(const FGameplayAttributeData& OldCriticalHitMultiplier) const;
	UFUNCTION()
	void OnRep_AccuracyRating(const FGameplayAttributeData& OldAccuracyRating) const;
	UFUNCTION()
	void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const;
	UFUNCTION()
	void OnRep_CastSpeed(const FGameplayAttributeData& OldCastSpeed) const;
	UFUNCTION()
	void OnRep_MaxLife(const FGameplayAttributeData& OldMaxLife) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	
	/*
	 *Secondary Attributes End
	*/
	
	/*
	 *Resource Attributes Start
	*/
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Life, Category="Resource Attributes")
	FGameplayAttributeData Life;
	ATTRIBUTE_ACCESSORS(UArpgAttributeSet, Life);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Mana, Category="Resource Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UArpgAttributeSet, Mana);

	UFUNCTION()
	void OnRep_Life(const FGameplayAttributeData& OldLife) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	/*
	*Resource Attributes End
	*/

private:
	void SetEffectProperties(const struct FGameplayEffectModCallbackData& Data, FEffectProperties& EffectProperties);
};



