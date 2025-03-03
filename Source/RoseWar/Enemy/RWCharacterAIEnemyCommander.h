// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RWCharacterAIEnemy.h"
#include "Interface/EnemyCommanderInterface.h"
#include "Interface/SwordAttackCheckInterface.h"
#include "RWCharacterAIEnemyCommander.generated.h"

class AAIControllerEnemyCommander;
class URWAIBehaviorComponent;

UCLASS()
class ROSEWAR_API ARWCharacterAIEnemyCommander : public ARWCharacterAIEnemy, public IEnemyCommanderInterface, public ISwordAttackCheckInterface
{
	GENERATED_BODY()
	
public:
	ARWCharacterAIEnemyCommander();

	/* IEnemyCommanderInterface Implement */
	virtual void EnemyWarinessCommand() override;
	virtual void EnemyAttackCommand() override;
	virtual void EnemyRetreatCommand() override;
	virtual void EnemyRestCommand() override;

	/* IClassIdentifierInterface Implement */
	virtual FName SetupClassName() override { return ClassName; }

	/* IAIInterface Implement */
	virtual void AttackByAI() override;

	/* ISwordAttackCheckInterface Implement */
	virtual class USkeletalMeshComponent* GetSwordBone() override;

/* Damaged */
public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


protected:
	virtual void BeginPlay() override;

/* Ability */
protected:
	virtual void SetDead();

private:
	void BeginAttack();
	void EndAttack();

/* Utility */
private:
	AAIControllerEnemyCommander* GetMyController();
	
/* Component */
private:
	UPROPERTY(VisibleAnywhere, Category = "Animation")
	TObjectPtr<URWAIBehaviorComponent> BehaviorComp;
};
