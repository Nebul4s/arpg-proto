// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ArpgAbilitySystemComponent.h"

#include "ArpgGameplayTags.h"
#include "AbilitySystem/Abilities/ArpgGameplayAbility.h"

void UArpgAbilitySystemComponent::AbilityActorInfoSet()
{
	//Multicast delegate which is called whenever a gameplayeffect is applied to this AbilitySystemComponent
	//AddUObject 1st param is the object instance whose method will be called, 2nd is the pointer to the UObject method to be called
	//UObject method just means a member function that belongs to a class derived from UObject
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UArpgAbilitySystemComponent::ClientEffectApplied);
}

void UArpgAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : Abilities)
	{
		/**
		 * FGameplayAbilitySpec is a struct hosted on the ASC. This defines what the ability is (what class, what level, input binding etc)
		 */
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const UArpgGameplayAbility* ArpgAbility = Cast<UArpgGameplayAbility>(AbilitySpec.Ability))
		{
			//DynamicAbilityTags is a FGameplayTagContainer property that holds a collection of gameplay tags that can be added or removed at runtime
			//For example for ability "firebolt" you could check if it has a tag that would alter how the ability works and if true change it to fire 3 firebolts in 1 go
			//As they can be added or removed at runtime this alteration could be a result of a temporary buff

			//in this context the tag to be added is the default InputTag like LMB which is defined in blueprint of the GameplayAbility
			AbilitySpec.DynamicAbilityTags.AddTag(ArpgAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void UArpgAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UArpgAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

void UArpgAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
}
