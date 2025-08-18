// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Character/ArpgCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "ArpgEnemy.generated.h"

class UBehaviorTree;
class AArpgAIController;

/**
 * 
 */
UCLASS()
class ARPG_API AArpgEnemy : public AArpgCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	AArpgEnemy();
	virtual void PossessedBy(AController* NewController) override;
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
	virtual void Die() override;
	/*
	*Combat interface end
	*/
	void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category="Combat")
	bool bIsStunned = false;

	UPROPERTY(BlueprintReadOnly, Category="Combat")
	float MaxWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	float LifeSpan = 5.f;
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character class defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character class defaults")
	ECharacterClass CharacterClass = ECharacterClass::Boss;
	
	UPROPERTY(EditAnywhere, Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AArpgAIController> ArpgAIController;
};
