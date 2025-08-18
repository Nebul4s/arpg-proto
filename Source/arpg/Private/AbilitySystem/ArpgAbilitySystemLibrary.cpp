// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ArpgAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "ArpgAbilityTypes.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Game/ArpgGameModeBase.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"

void UArpgAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass)
{
	AArpgGameModeBase* ArpgGameMode = Cast<AArpgGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (ArpgGameMode == nullptr) return;

	UCharacterClassInfo* CharacterClassInfo = ArpgGameMode->CharacterClassInfo;
	if (CharacterClassInfo == nullptr) return;
	for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
	const FCharacterClassDefaultInfo& DefaultInfo = CharacterClassInfo->GetCharacterClassDefaultInfo(CharacterClass);
	for (auto AbilityClass : DefaultInfo.StartupAbilities)
	{
		ICombatInterface* CombatInterface = Cast<ICombatInterface>(ASC->GetAvatarActor());
		if (CombatInterface)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, CombatInterface->GetPlayerLevel());
			ASC->GiveAbility(AbilitySpec);
		}
	}
}

bool UArpgAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FArpgGameplayEffectContext* ArpgContext = static_cast<const FArpgGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return ArpgContext->IsBlockedHit();
	};
	return false;
}

bool UArpgAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FArpgGameplayEffectContext* ArpgContext = static_cast<const FArpgGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return ArpgContext->IsCriticalHit();
	};
	return false;
}

void UArpgAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bIsBlockedHit)
{
	if (FArpgGameplayEffectContext* ArpgContext = static_cast<FArpgGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		ArpgContext->SetIsCriticalHit(bIsBlockedHit);
	};
}

void UArpgAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, bool bIsCriticalHit)
{
	if (FArpgGameplayEffectContext* ArpgContext = static_cast<FArpgGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		ArpgContext->SetIsCriticalHit(bIsCriticalHit);
	};
}
