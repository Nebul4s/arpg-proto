// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "ArpgPlayerController.generated.h"

class UArpgInputConfig;
class UInputMappingContext;
class UInputAction;
class IEnemyInterface;
class UArpgAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class ARPG_API AArpgPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AArpgPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> ArpgContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const struct FInputActionValue& InputActionValue);

	void CursorTrace();
	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> CurrentActor;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UArpgInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UArpgAbilitySystemComponent> ArpgAbilitySystemComponent;
	UArpgAbilitySystemComponent* GetASC();
};
