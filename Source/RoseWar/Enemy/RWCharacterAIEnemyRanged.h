// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RWCharacterAIEnemy.h"
#include "Interface/BowAttackCheckInterface.h"
#include "RWCharacterAIEnemyRanged.generated.h"

class AAIControllerEnemyRanged;
class URWAIBehaviorComponent;

UCLASS()
class ROSEWAR_API ARWCharacterAIEnemyRanged : public ARWCharacterAIEnemy, public IBowAttackCheckInterface
{
	GENERATED_BODY()

public:
	ARWCharacterAIEnemyRanged();

	/* IAIInterface Implement */
	virtual void AttackByAI() override;
	virtual float GetAttackRange() override;

	/* IClassIdentifierInterface Implement */
	virtual FName SetupClassName() override { return ClassName; }

	/* IBowAttackCheckInterface Implement */
	virtual void CreateArrow() override;
	virtual void ReleaseArrow() override;

	/* IEnemyReadyForBattleInterface Implement */
	virtual void ReadyForBattle() override;
	virtual void ReadyForRest() override;

	/* Damaged */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;

/* Ability */
protected:
	virtual void SetDead() override;

private:
	void BeginAttack();
	void EndAttack();

/* Utility */
private:
	AAIControllerEnemyRanged* GetMyController();

	UPROPERTY(VisibleAnywhere, Category = "Arrow")
	TSubclassOf<class ARWArrow> ArrowClass;

	UPROPERTY(VisibleAnywhere, Category = "Arrow")
	TObjectPtr<UStaticMesh> ArrowMesh;

/* Component */
private:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<USkeletalMeshComponent> QuiverComp;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> ArrowMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Animation")
	TObjectPtr<URWAIBehaviorComponent> BehaviorComp;
};
