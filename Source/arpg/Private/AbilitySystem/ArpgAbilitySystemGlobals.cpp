// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ArpgAbilitySystemGlobals.h"

#include "ArpgAbilityTypes.h"

FGameplayEffectContext* UArpgAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FArpgGameplayEffectContext();
}
