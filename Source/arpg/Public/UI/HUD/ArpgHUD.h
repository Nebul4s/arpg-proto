// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ArpgHUD.generated.h"

class UArpgUserWidget;
/**
 * 
 */
UCLASS()
class ARPG_API AArpgHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TObjectPtr<UArpgUserWidget> OverlayWidget;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UArpgUserWidget> OverlayWidgetClass;

};
