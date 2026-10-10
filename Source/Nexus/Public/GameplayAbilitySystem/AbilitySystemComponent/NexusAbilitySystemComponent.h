// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "NexusAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NEXUS_API UNexusAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public: // public Scope for Variables
	
protected: // protected Scope for Variables
	TArray<FGameplayAbilitySpec> LastActivatableAbilities;
	
	
public: // public Scope for Functions
	UNexusAbilitySystemComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected: // protected Scope for Functions
	virtual void BeginPlay() override;
	
	virtual void OnRep_ActivateAbilities() override;
};
