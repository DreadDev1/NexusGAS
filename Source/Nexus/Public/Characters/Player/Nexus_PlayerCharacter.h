// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Nexus_BaseCharacter.h"
#include "Nexus_PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class NEXUS_API ANexus_PlayerCharacter : public ANexus_BaseCharacter
{
	GENERATED_BODY()

public:
	ANexus_PlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
#pragma region Set Camera 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nexus|Camera")
	USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nexus|Camera")
	UCameraComponent* FollowCamera;
#pragma endregion
	
protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

public:

};
