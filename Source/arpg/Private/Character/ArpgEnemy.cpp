// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ArpgEnemy.h"

#include "AbilitySystem/ArpgAbilitySystemComponent.h"
#include "AbilitySystem/ArpgAttributeSet.h"
#include "arpg/arpg.h"
#include "ArpgGameplayTags.h"
#include "AbilitySystem/ArpgAbilitySystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"


AArpgEnemy::AArpgEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UArpgAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UArpgAttributeSet>("AttributeSet");
}

void AArpgEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AArpgEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 AArpgEnemy::GetPlayerLevel()
{
	return Level;
}

void AArpgEnemy::Die()
{
	SetLifeSpan(LifeSpan);
	Super::Die();
}

void AArpgEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	InitAbilityActorInfo();
	if (HasAuthority())
	{
		UArpgAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent);
	}
	
	AbilitySystemComponent->RegisterGameplayTagEvent(FArpgGameplayTags::Get().Stun, EGameplayTagEventType::NewOrRemoved).AddUObject(
		this, &AArpgEnemy::StunTagChanged
	);
}

void AArpgEnemy::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bIsStunned = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bIsStunned ? 0.f : MaxWalkSpeed;
}

void AArpgEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UArpgAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	if (HasAuthority())
	{
		InitializeDefaultAttributes();
	}
}
