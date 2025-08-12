// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ArpgCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/ArpgAbilitySystemComponent.h"

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

FVector AArpgCharacterBase::GetCombatSocketLocation()
{
	check(Weapon);

	if (!Weapon->DoesSocketExist(WeaponTipSocketName))
	{
		UE_LOG(LogTemp, Error, TEXT("Socket %s does NOT exist on weapon mesh %s"),
			*WeaponTipSocketName.ToString(),
			*Weapon->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Socket %s exists. Location: %s"),
			*WeaponTipSocketName.ToString(),
			*Weapon->GetSocketLocation(WeaponTipSocketName).ToString());
	}

	
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

void AArpgCharacterBase::InitAbilityActorInfo()
{
}

void AArpgCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectClass, float level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(EffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(EffectClass, 1.f, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AArpgCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultResourceAttributes, 1.f);
}

void AArpgCharacterBase::AddCharacterAbilities()
{
	UArpgAbilitySystemComponent* ArpgASC = CastChecked<UArpgAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	ArpgASC->AddCharacterAbilities(StartupAbilities);
}


