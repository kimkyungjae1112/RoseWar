// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/RWAnimMontageData.h"
#include "RWAIBehaviorComponent.generated.h"

class UAnimInstance;
class UAnimMontage;
class ACharacter;

DECLARE_DELEGATE(FOnCompAttackFinished)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROSEWAR_API URWAIBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URWAIBehaviorComponent();

protected:
	virtual void BeginPlay() override;

public:
	FOnCompAttackFinished OnCompAttackFinished;

public:
	void Attack();
	void Dead();
	void Wariness();
	void UnWariness();

private:
	void EndAttack(UAnimMontage* Target, bool IsProperlyEnded);
	void EndWariness(UAnimMontage* Target, bool IsProperlyEnded);
	void EndUnWariness(UAnimMontage* Target, bool IsProperlyEnded);

/* Util */
private:
	UPROPERTY(VisibleAnywhere, Category = "Util")
	TObjectPtr<ACharacter> Character;

	UPROPERTY(VisibleAnywhere, Category = "Util")
	TObjectPtr<UAnimInstance> Anim;

/* Data */
private:
	UPROPERTY(VisibleInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = "true"))
	FRWAnimMontageData AnimMontageData;
};
