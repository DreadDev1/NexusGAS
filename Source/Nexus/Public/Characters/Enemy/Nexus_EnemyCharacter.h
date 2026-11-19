// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Nexus_BaseCharacter.h"
#include "Nexus_EnemyCharacter.generated.h"

UCLASS()
class NEXUS_API ANexus_EnemyCharacter : public ANexus_BaseCharacter
{
	GENERATED_BODY()

public:
	ANexus_EnemyCharacter();

protected:
	virtual void BeginPlay() override;
};
