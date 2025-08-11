// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ArpgInputConfig.h"

const UInputAction* UArpgInputConfig::FindAbilityInputActionByTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FArpgInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Display, TEXT("No input action found for tag %s, in config %s"), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
