// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemy/Nexus_EnemyCharacter.h"


// Sets default values
ANexus_EnemyCharacter::ANexus_EnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANexus_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		GrantAbilities(StartingAbilities); // already returns early if not on the server
	} 
	
}