// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemComponent.h"
#include "ArpgAbilityTypes.h"
#include "ArpgGameplayTags.h"
#include "AbilitySystem/ArpgAbilitySystemLibrary.h"
#include "AbilitySystem/ArpgAttributeSet.h"

struct ArpgDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitMultiplier);
	ArpgDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UArpgAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UArpgAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UArpgAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UArpgAttributeSet, CriticalHitMultiplier, Source, false);
	}
};

static const ArpgDamageStatics& GetArpgDamageStatics()
{
	static ArpgDamageStatics DamageStatics;

	return DamageStatics;
};

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add((GetArpgDamageStatics().ArmorDef));
	RelevantAttributesToCapture.Add((GetArpgDamageStatics().BlockChanceDef));
	RelevantAttributesToCapture.Add((GetArpgDamageStatics().CriticalHitChanceDef));
	RelevantAttributesToCapture.Add((GetArpgDamageStatics().CriticalHitMultiplierDef));
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceActor = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetActor = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = SourceTags;
	EvaluateParams.TargetTags = TargetTags;

	//Get damage set by caller mag
	float Damage = 0.f;
	for (const auto& Pair : FArpgGameplayTags::Get().DamageTypesToResistances)
	{
		const float DamageTypeValue = Spec.GetSetByCallerMagnitude(Pair.Key);
		Damage += DamageTypeValue;
	}
	
	//blockchance, if block prevent damage
	float TargetBlockChance = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetArpgDamageStatics().BlockChanceDef, EvaluateParams, TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(TargetBlockChance, 0.f);
	const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;

	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	UArpgAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bBlocked);
	
	if (bBlocked) Damage = 0.f;

	//armor
	float TargetArmor = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetArpgDamageStatics().ArmorDef, EvaluateParams, TargetArmor);
	TargetArmor = FMath::Max<float>(TargetArmor, 0.f);
	Damage *= (100 - TargetArmor) / 100.f;

	//critical hits
	float SourceCriticalHitChance = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetArpgDamageStatics().CriticalHitChanceDef, EvaluateParams, SourceCriticalHitChance);
	SourceCriticalHitChance = FMath::Max<float>(SourceCriticalHitChance, 0.f);
	float SourceCriticalHitMultiplier = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetArpgDamageStatics().CriticalHitMultiplierDef, EvaluateParams, SourceCriticalHitMultiplier);
	SourceCriticalHitMultiplier = FMath::Max<float>(SourceCriticalHitMultiplier, 0.f);

	const bool bIsCriticalHit = FMath::RandRange(1, 100) < SourceCriticalHitChance;
	UArpgAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bIsCriticalHit);
	
	if (bIsCriticalHit) Damage *= SourceCriticalHitMultiplier / 100.f;
	
	const FGameplayModifierEvaluatedData EvaluatedData(UArpgAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
