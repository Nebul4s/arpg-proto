// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/ArpgUserWidget.h"

void UArpgUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
