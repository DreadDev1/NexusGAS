// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/NexusGameplayAbility.h"

UNexusGameplayAbility::UNexusGameplayAbility()
{
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("_Nexus.Abilities.Active")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("_Nexus.State.Dead")));
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

bool UNexusGameplayAbility::HasPC() const
{
	const APawn* PawnObject = Cast<APawn>(GetAvatarActorFromActorInfo());
	if (!PawnObject) { return false; }
	return PawnObject->GetController()->IsA<APlayerController>();
}
