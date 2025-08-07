// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ArpgPlayerState.h"

#include "AbilitySystem/ArpgAbilitySystemComponent.h"
#include "AbilitySystem/ArpgAttributeSet.h"

AArpgPlayerState::AArpgPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UArpgAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UArpgAttributeSet>("AttributeSet");
	
	SetNetUpdateFrequency(100.f);
}

UAbilitySystemComponent* AArpgPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
