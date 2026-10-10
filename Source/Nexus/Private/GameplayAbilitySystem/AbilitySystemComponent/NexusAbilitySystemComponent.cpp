// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/AbilitySystemComponent/NexusAbilitySystemComponent.h"
#include "Characters/Nexus_BaseCharacter.h"

UNexusAbilitySystemComponent::UNexusAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNexusAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UNexusAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();
	
	ANexus_BaseCharacter* Character = Cast<ANexus_BaseCharacter>(GetOwner());
	if (!Character) return;
	
	Character->SendAbilitiesChangedEvent();
	
	bool bAbilitiesChanged = false;
	if (LastActivatableAbilities.Num() != ActivatableAbilities.Items.Num())
	{
		bAbilitiesChanged = true;
	} else
	{
		for (int32 i = 0; i < LastActivatableAbilities.Num(); i++)
		{
			if (LastActivatableAbilities[i].Ability != ActivatableAbilities.Items[i].Ability)
			{
				bAbilitiesChanged = true;
				break;
			}
		}
	}

	if (bAbilitiesChanged)
	{
		Character->SendAbilitiesChangedEvent();
		LastActivatableAbilities = ActivatableAbilities.Items;
	}
}

void UNexusAbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

