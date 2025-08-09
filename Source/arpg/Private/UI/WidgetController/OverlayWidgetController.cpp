// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/ArpgAbilitySystemComponent.h"
#include "AbilitySystem/ArpgAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UArpgAttributeSet* ArpgAttributeSet = CastChecked<UArpgAttributeSet>(AttributeSet);

	OnLifeChanged.Broadcast(ArpgAttributeSet->GetLife());
	OnMaxLifeChanged.Broadcast(ArpgAttributeSet->GetMaxLife());
	OnManaChanged.Broadcast(ArpgAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(ArpgAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UArpgAttributeSet* ArpgAttributeSet = CastChecked<UArpgAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	ArpgAttributeSet->GetLifeAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnLifeChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	ArpgAttributeSet->GetMaxLifeAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnMaxLifeChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	ArpgAttributeSet->GetManaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	ArpgAttributeSet->GetMaxManaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);

	Cast<UArpgAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (auto Tag: AssetTags)
			{
				const FString Msg = FString::Printf(TEXT("GE Tag %s"), *Tag.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Msg);
			}
		}
	);
}
