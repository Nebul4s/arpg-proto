// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/ArpgHUD.h"

#include "Blueprint/UserWidget.h"
#include "Components/Overlay.h"
#include "UI/Widget/ArpgUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AArpgHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

void AArpgHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay widget class uninitialized"))
	checkf(OverlayWidgetControllerClass, TEXT("Overlay widget controller class uninitialized"))
	
	UArpgUserWidget* Widget = CreateWidget<UArpgUserWidget>(GetWorld(), OverlayWidgetClass);

	OverlayWidget = Cast<UArpgUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	Widget->AddToViewport();
}