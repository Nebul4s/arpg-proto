// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ArpgEnemy.h"

#include "AbilitySystem/ArpgAbilitySystemComponent.h"
#include "AbilitySystem/ArpgAttributeSet.h"
#include "arpg/arpg.h"
#include "ArpgGameplayTags.h"
#include "AbilitySystem/ArpgAbilitySystemLibrary.h"
#include "AI/ArpgAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


AArpgEnemy::AArpgEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UArpgAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	
	AttributeSet = CreateDefaultSubobject<UArpgAttributeSet>("AttributeSet");
}

void AArpgEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	ArpgAIController = Cast<AArpgAIController>(NewController);

	ArpgAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	ArpgAIController->RunBehaviorTree(BehaviorTree);

	ArpgAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsStunned"), false);
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

void AArpgEnemy::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* AArpgEnemy::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}

void AArpgEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	InitAbilityActorInfo();
	if (HasAuthority())
	{
		UArpgAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent, CharacterClass);
	}
	
	AbilitySystemComponent->RegisterGameplayTagEvent(FArpgGameplayTags::Get().Stun, EGameplayTagEventType::NewOrRemoved).AddUObject(
		this, &AArpgEnemy::StunTagChanged
	);
}

void AArpgEnemy::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bIsStunned = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bIsStunned ? 0.f : MaxWalkSpeed;
	if (ArpgAIController && ArpgAIController->GetBlackboardComponent())
	{
		ArpgAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsStunned"), bIsStunned);
	}
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