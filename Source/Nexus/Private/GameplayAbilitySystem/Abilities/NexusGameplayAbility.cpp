// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/NexusGameplayAbility.h"

UNexusGameplayAbility::UNexusGameplayAbility()
{
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("_Nexus.Abilities.Active")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("_Nexus.State.Dead")));
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}
