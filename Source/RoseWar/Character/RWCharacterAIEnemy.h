// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RWCharacterAIBase.h"
#include "Interface/EnemyReadyForBattleInterface.h"
#include "RWCharacterAIEnemy.generated.h"

UCLASS()
class ROSEWAR_API ARWCharacterAIEnemy : public ARWCharacterAIBase, public IEnemyReadyForBattleInterface
{
	GENERATED_BODY()

public:
	ARWCharacterAIEnemy();

	static FOnWarinessCommand OnEnemyWarinessCommand;
	static FOnAttackCommand OnEnemyAttackCommand;
	static FOnRetreatCommand OnEnemyRetreatCommand;
	static FOnRestCommand OnEnemyRestCommand;

	/* IGenericTeamAgentInterface Implement */
	virtual FGenericTeamId GetGenericTeamId() const override;

	/* IEnemyReadyForBattleInterface Implement */
	virtual void ReadyForBattle() override;
	virtual void ReadyForRest() override;

	/* Damaged */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	float GetCurrentHp() const;
	float GetMaxHp() const;

/* Ability */
protected:
	virtual void SetDead() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<USkeletalMeshComponent> HeadMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<USkeletalMeshComponent> HairMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<USkeletalMeshComponent> EyeMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<USkeletalMeshComponent> HandMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<USkeletalMeshComponent> LegMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<USkeletalMeshComponent> FeetMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<USkeletalMeshComponent> LeftWeaponMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<USkeletalMeshComponent> RightWeaponMeshComp;
};
