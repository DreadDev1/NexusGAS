// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Nexus_BaseCharacter.h"
#include "GameplayAbilitySystem/AbilitySystemComponent/NexusAbilitySystemComponent.h"
#include "GameplayAbilitySystem/Attributes/BaseAttributeSet.h"

ANexus_BaseCharacter::ANexus_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

#pragma region AbilitySystem Component
	AbilitySystemComponent = CreateDefaultSubobject<UNexusAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(ASCReplicationMode);
#pragma endregion
	
	BaseAttributeSet = CreateDefaultSubobject<UBaseAttributeSet>("AttributeSet");
}

void ANexus_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ANexus_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#pragma region AbilitySystem Component
UAbilitySystemComponent* ANexus_BaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

TArray<FGameplayAbilitySpecHandle> ANexus_BaseCharacter::GrantAbilities(
	TArray<TSubclassOf<UGameplayAbility>> AbilitiesToGrant)
{
	if (!AbilitySystemComponent || !HasAuthority()) { return TArray<FGameplayAbilitySpecHandle>(); }

	TArray<FGameplayAbilitySpecHandle> AbilityHandles;
	for (TSubclassOf<UGameplayAbility> Ability : AbilitiesToGrant)
	{
		FGameplayAbilitySpecHandle SpecHandle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(
			Ability, 1, -1, this
		));
		AbilityHandles.Add(SpecHandle);
	}

	SendAbilitiesChangedEvent();
	return AbilityHandles;
}

void ANexus_BaseCharacter::RemoveAbilities(TArray<FGameplayAbilitySpecHandle> AbilityHandlesToRemove)
{
	if (!AbilitySystemComponent || !HasAuthority()) return;

	for (FGameplayAbilitySpecHandle AbilityHandle : AbilityHandlesToRemove)
	{
		AbilitySystemComponent->ClearAbility(AbilityHandle);
	}

	SendAbilitiesChangedEvent();
}

void ANexus_BaseCharacter::SendAbilitiesChangedEvent()
{
	FGameplayEventData EventData;
	EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("_Nexus.Events.Abilities.Changed"));
	EventData.Instigator = this;
	EventData.Target = this;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, EventData.EventTag, EventData);
}
#pragma endregion