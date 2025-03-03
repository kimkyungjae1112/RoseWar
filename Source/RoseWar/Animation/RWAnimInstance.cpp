// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/RWAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

URWAnimInstance::URWAnimInstance()
{
	MovingThreshold = 3.f;
	JumpingThreshold = 30.f;
}

void URWAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ACharacter>(GetOwningActor());
	if (Character)
	{
		Movement = Character->GetCharacterMovement();
		ensure(Movement);
	}
}

void URWAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size();
		Angle = UKismetMathLibrary::InverseTransformDirection(Character->GetActorTransform(), Velocity);
		bIsIdle = GroundSpeed < MovingThreshold;
		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling & (Velocity.Z >= JumpingThreshold);
	}
}
