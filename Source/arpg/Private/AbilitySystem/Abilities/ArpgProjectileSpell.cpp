// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ArpgProjectileSpell.h"

#include "Actor/ArpgProjectile.h"
#include "Interaction/CombatInterface.h"

void UArpgProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const bool bIsServer = HasAuthority(&ActivationInfo);
	if (!bIsServer) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		//TODO:: handle rotation
		
		AArpgProjectile* ProjectileToSpawn = GetWorld()->SpawnActorDeferred<AArpgProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
			);

		//TODO:: give the projectile  GE for damage
		
		ProjectileToSpawn->FinishSpawning(SpawnTransform);
	}
	

}
