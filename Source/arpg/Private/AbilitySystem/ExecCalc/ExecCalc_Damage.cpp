// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/ArpgAttributeSet.h"

struct ArpgDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	ArpgDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UArpgAttributeSet, Armor, Target, false);
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

	float Armor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetArpgDamageStatics().ArmorDef, EvaluateParams, Armor);
	Armor = FMath::Max(0.f, Armor);

	const FGameplayModifierEvaluatedData EvaluatedData(GetArpgDamageStatics().ArmorProperty, EGameplayModOp::Additive, Armor);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
