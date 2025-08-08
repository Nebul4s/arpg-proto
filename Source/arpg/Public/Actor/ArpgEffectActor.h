// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArpgEffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class ARPG_API AArpgEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AArpgEffectActor();


protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass);
	
	UPROPERTY(EditAnywhere, Category="Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
};
