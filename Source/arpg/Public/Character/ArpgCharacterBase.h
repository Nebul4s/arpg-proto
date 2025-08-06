// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ArpgCharacterBase.generated.h"

UCLASS(Abstract)
class ARPG_API AArpgCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AArpgCharacterBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
};
