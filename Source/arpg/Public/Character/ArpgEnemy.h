// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ArpgCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "ArpgEnemy.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API AArpgEnemy : public AArpgCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	AArpgEnemy();
	
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
};
