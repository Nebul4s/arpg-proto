// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "ArpgAttributeSet.generated.h"

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

	//Resource Attributes Start
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Life, Category="Resource Attributes")
	FGameplayAttributeData Life;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxLife, Category="Resource Attributes")
	FGameplayAttributeData MaxLife;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Mana, Category="Resource Attributes")
	FGameplayAttributeData Mana;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxMana, Category="Resource Attributes")
	FGameplayAttributeData MaxMana;

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


