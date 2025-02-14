// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PFAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UPFAnimInstance::UPFAnimInstance()
{
	MovingThreshould = 5.0f;
	JumpingThreshould = 100.0f;
}

void UPFAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner)
	{
		UE_LOG(LogTemp, Log, TEXT("ads"));
		Movement = Owner->GetCharacterMovement();
	}
}

void UPFAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D();
		bIsIdle = GroundSpeed < MovingThreshould;
		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshould);
	}
}
