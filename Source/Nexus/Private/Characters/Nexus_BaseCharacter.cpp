// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Nexus_BaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySystem/Attributes/BaseAttributeSet.h"

ANexus_BaseCharacter::ANexus_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

#pragma region AbilitySystem Component
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
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

UAbilitySystemComponent* ANexus_BaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}