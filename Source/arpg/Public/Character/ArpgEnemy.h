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

	/*
	 *Enemy interface
	 */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/*
	*Enemy interface end
	*/

	/*
	*Combat interface
	*/
	virtual int32 GetPlayerLevel() override;
	/*
	*Combat interface end
	*/

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character class defaults")
	int32 Level = 1;
};
