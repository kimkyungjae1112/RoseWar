// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RWAnimInstance.generated.h"

class ACharacter;
class UCharacterMovementComponent;

UCLASS()
class ROSEWAR_API URWAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	URWAnimInstance();

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
	uint8 bIsIdle : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
	uint8 bIsFalling : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
	uint8 bIsJumping : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
	uint8 bIsWariness : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
	float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
	float MovingThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
	float JumpingThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
	FVector Angle;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ACharacter> Character;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCharacterMovementComponent> Movement;
};
