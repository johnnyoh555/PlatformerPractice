// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PFCharacterControlData.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERPRACTICE_API UPFCharacterControlData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPFCharacterControlData();

	UPROPERTY(EditAnywhere, Category = Pawn)
	uint32 bUseControllerRotationYaw : 1;

	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	uint32 bOrientRotationToMovement : 1;

	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	uint32 bUseControllerDesiredRotation : 1;

	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	FRotator RotationRate;

	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	float BrakingDecelerationWalking;

	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	float MinAnalogWalkSpeed;

	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	float MaxWalkSpeed;
	
	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	float WalkSpeed;

	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	float RunSpeed;

	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	float JumpZVelocity;
	
	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	float AirControl;

	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	float GravityScale;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	float TargetArmLength;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	FRotator RelativeRotation;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	uint32 bUsePawnControlRotation : 1;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	uint32 bInheritPitch : 1;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	uint32 bInheritYaw : 1;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	uint32 bInheritRoll : 1;

	UPROPERTY(EditAnywhere, Category = SpringArm)
	uint32 bDoCollisionTest : 1;

};