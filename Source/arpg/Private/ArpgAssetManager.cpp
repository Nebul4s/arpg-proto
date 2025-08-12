// Fill out your copyright notice in the Description page of Project Settings.


#include "ArpgAssetManager.h"
#include "ArpgGameplayTags.h"

UArpgAssetManager& UArpgAssetManager::Get()
{
	check(GEngine);

	UArpgAssetManager* ArpgAssetManager = Cast<UArpgAssetManager>(GEngine->AssetManager);
	return *ArpgAssetManager;
}

void UArpgAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FArpgGameplayTags::InitializeNativeGameplayTags();
	UAbilitySystemGlobals::Get().InitGlobalData();
}
