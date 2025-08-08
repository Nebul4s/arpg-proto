// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/ArpgAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UArpgAttributeSet* ArpgAttributeSet = CastChecked<UArpgAttributeSet>(AttributeSet);

	OnLifeChanged.Broadcast(ArpgAttributeSet->GetLife());
	OnMaxLifeChanged.Broadcast(ArpgAttributeSet->GetMaxLife());
	OnManaChanged.Broadcast(ArpgAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(ArpgAttributeSet->GetMaxMana());
}
