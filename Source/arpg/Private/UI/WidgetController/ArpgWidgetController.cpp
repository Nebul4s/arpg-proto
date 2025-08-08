// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/ArpgWidgetController.h"

void UArpgWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams)
{
	PlayerController = WidgetControllerParams.PlayerController;
	PlayerState = WidgetControllerParams.PlayerState;
	AbilitySystemComponent = WidgetControllerParams.AbilitySystemComponent;
	AttributeSet = WidgetControllerParams.AttributeSet;
}

void UArpgWidgetController::BroadcastInitialValues()
{
}
