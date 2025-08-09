// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ArpgCharacterBase.h"

#include "AbilitySystemComponent.h"

AArpgCharacterBase::AArpgCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

UAbilitySystemComponent* AArpgCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AArpgCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	
}

void AArpgCharacterBase::InitAbilityActorInfo()
{
}

void AArpgCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectClass, float level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(EffectClass);
	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(EffectClass, 1.f, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AArpgCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
}


