// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AbilitySystemGlobals.h"
#include "ArpgAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UArpgAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static UArpgAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
