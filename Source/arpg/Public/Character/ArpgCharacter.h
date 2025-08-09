// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ArpgCharacterBase.h"
#include "ArpgCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API AArpgCharacter : public AArpgCharacterBase
{
	GENERATED_BODY()
public:
	AArpgCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
private:
	virtual void InitAbilityActorInfo() override;
};
