// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ArpgProjectileSpell.h"
#include "Components/SphereComponent.h"
#include "Actor/ArpgProjectile.h"
#include "Interaction/CombatInterface.h"

void UArpgProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


	

}

void UArpgProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		Rotation.Pitch = 0.f;
		
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());
		
		AArpgProjectile* ProjectileToSpawn = GetWorld()->SpawnActorDeferred<AArpgProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
			);

		// ignore overlap on casting actor
		if (ProjectileToSpawn && GetAvatarActorFromActorInfo())
		{
			ProjectileToSpawn->Sphere->IgnoreActorWhenMoving(GetAvatarActorFromActorInfo(), true);
		}


		//TODO:: give the projectile  GE for damage
		
		ProjectileToSpawn->FinishSpawning(SpawnTransform);
	}
}
