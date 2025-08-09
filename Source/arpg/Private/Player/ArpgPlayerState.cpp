// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ArpgPlayerState.h"

#include "AbilitySystem/ArpgAbilitySystemComponent.h"
#include "AbilitySystem/ArpgAttributeSet.h"
#include "Net/UnrealNetwork.h"

AArpgPlayerState::AArpgPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UArpgAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UArpgAttributeSet>("AttributeSet");
	
	SetNetUpdateFrequency(100.f);
}

void AArpgPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AArpgPlayerState, Level);
}

UAbilitySystemComponent* AArpgPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AArpgPlayerState::OnRep_Level(int32 OldLevel) const
{
}
