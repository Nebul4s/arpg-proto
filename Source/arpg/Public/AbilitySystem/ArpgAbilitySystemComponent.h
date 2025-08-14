// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ArpgAbilitySystemComponent.generated.h"

/*
 * When variable of type FEffectAssetTags is Broadcast this delegate will call
 * every function bound to it with the same tagcontainer.
 * Multicast delegate can be bound to many functions where as DECLARE_DELEGATE_OneParam
 * would only be able to be bound to 1 and any new binding would override the previous
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer&);

/**
 * 
 */
UCLASS()
class ARPG_API UArpgAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityActorInfoSet();

	FEffectAssetTags EffectAssetTags;

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities);

	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
protected:
	/*
	 * Client specifier marks this function as "Remote Procedure Call" aka RPC that should be executed on the client machine
	 * When the function is called on the server, the engine sends a network message to the owning client to exec the function
	 *
	 * Reliable means that this RPC must be delivered and executed, even if it requires resending the packet.
	 * Other option "Unreliable" is faster but it may be dropped
	 */
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
};
