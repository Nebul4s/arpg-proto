// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ArpgAttributeSet.generated.h"


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
	
	//Resource Attributes Start
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Life, Category="Resource Attributes")
	FGameplayAttributeData Life;
	ATTRIBUTE_ACCESSORS(UArpgAttributeSet, Life);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxLife, Category="Resource Attributes")
	FGameplayAttributeData MaxLife;
	ATTRIBUTE_ACCESSORS(UArpgAttributeSet, MaxLife);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Mana, Category="Resource Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UArpgAttributeSet, Mana);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxMana, Category="Resource Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UArpgAttributeSet, MaxMana);

	UFUNCTION()
	void OnRep_Life(const FGameplayAttributeData& OldLife) const;
	UFUNCTION()
	void OnRep_MaxLife(const FGameplayAttributeData& OldMaxLife) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	//Resource Attributes End
};


