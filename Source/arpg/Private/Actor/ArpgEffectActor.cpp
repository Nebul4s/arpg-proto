// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/ArpgEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/ArpgAttributeSet.h"
#include "Components/SphereComponent.h"

AArpgEffectActor::AArpgEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AArpgEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: This is bad, change to apply gameplay effect
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UArpgAttributeSet* AttributeSet = Cast<UArpgAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UArpgAttributeSet::StaticClass()));
		UArpgAttributeSet* MutableAttributeSet= const_cast<UArpgAttributeSet*>(AttributeSet);
		MutableAttributeSet->SetLife(AttributeSet->GetLife() - 20.f);
		Destroy();
	};
}

void AArpgEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AArpgEffectActor::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AArpgEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AArpgEffectActor::EndOverlap);
}


