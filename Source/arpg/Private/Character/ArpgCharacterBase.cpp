// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ArpgCharacterBase.h"

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


