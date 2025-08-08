// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/ArpgHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/ArpgUserWidget.h"

void AArpgHUD::BeginPlay()
{
	Super::BeginPlay();
	
	
	UArpgUserWidget* Widget = CreateWidget<UArpgUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
