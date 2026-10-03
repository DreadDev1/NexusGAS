// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Nexus_BaseCharacter.generated.h"

UCLASS()
class NEXUS_API ANexus_BaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ANexus_BaseCharacter();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

#pragma region AbilitySystem Component
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nexus|AbilitySystem")
	UAbilitySystemComponent* AbilitySystemComponent;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nexus|AbilitySystem")
	EGameplayEffectReplicationMode ASCReplicationMode = EGameplayEffectReplicationMode::Mixed;
#pragma endregion
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nexus|GameplayAbilitySystem|Attributes")
	class UBaseAttributeSet* BaseAttributeSet;
};
