// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ArpgAbilitySystemComponent.h"

void UArpgAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UArpgAbilitySystemComponent::EffectApplied);
}

void UArpgAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	
}
