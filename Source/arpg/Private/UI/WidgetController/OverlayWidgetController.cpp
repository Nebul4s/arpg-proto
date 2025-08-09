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
		ArpgAttributeSet->GetLifeAttribute()).AddUObject(this, &UOverlayWidgetController::LifeChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		ArpgAttributeSet->GetMaxLifeAttribute()).AddUObject(this, &UOverlayWidgetController::MaxLifeChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		ArpgAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		ArpgAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);

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

void UOverlayWidgetController::LifeChanged(const FOnAttributeChangeData& Data) const
{
	OnLifeChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxLifeChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxLifeChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
