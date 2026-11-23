// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Nexus_BaseCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->RegisterGameplayTagEvent(
			FGameplayTag::RequestGameplayTag(FName("_Nexus.State.Dead")))
			.AddUObject(this, &ANexus_BaseCharacter::OnDeadTagChanged);
	}
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

void ANexus_BaseCharacter::Server_SendGameplayEventToSelf_Implementation(FGameplayEventData EventData)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, EventData.EventTag, EventData);
}
#pragma endregion

void ANexus_BaseCharacter::HandleDeath_Implementation()
{
	if (IsTemplate()) return;
	
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->DisableMovement();
	
	FVector Impulse = GetActorForwardVector() * -10000.f;
	Impulse.Z = 15000.f;
	GetMesh()->AddImpulseAtLocation(Impulse, GetActorLocation());
}

void ANexus_BaseCharacter::OnDeadTagChanged(const FGameplayTag CallbackTag, const int32 NewCount)
{
	if (NewCount > 0)
	{
		HandleDeath();
	}
}