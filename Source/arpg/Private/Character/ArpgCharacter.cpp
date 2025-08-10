// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ArpgCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/ArpgAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/ArpgPlayerController.h"
#include "Player/ArpgPlayerState.h"
#include "UI/HUD/ArpgHUD.h"

AArpgCharacter::AArpgCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AArpgCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//Init ability actor info for the server
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void AArpgCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//Init ability actor info for the client
	InitAbilityActorInfo();
}

int32 AArpgCharacter::GetPlayerLevel()
{
	const AArpgPlayerState* ArpgPlayerState = GetPlayerState<AArpgPlayerState>();
	check(ArpgPlayerState);
	return ArpgPlayerState->GetPlayerLevel();
}

void AArpgCharacter::InitAbilityActorInfo()
{
	AArpgPlayerState* ArpgPlayerState = GetPlayerState<AArpgPlayerState>();
	check(ArpgPlayerState);

	ArpgPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(ArpgPlayerState, this);
	Cast<UArpgAbilitySystemComponent>(ArpgPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = ArpgPlayerState->GetAbilitySystemComponent();
	AttributeSet = ArpgPlayerState->GetAttributeSet();

	if (AArpgPlayerController* PlayerController = Cast<AArpgPlayerController>(GetController()))
	{
		if (AArpgHUD* ArpgHUD =	Cast<AArpgHUD>(PlayerController->GetHUD()))
		{
			ArpgHUD->InitOverlay(PlayerController, ArpgPlayerState, AbilitySystemComponent, AttributeSet);
		};
	};
	InitializeDefaultAttributes();
}
