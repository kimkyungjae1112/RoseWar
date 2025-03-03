// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RWCharacterAIEnemy.h"
#include "Interface/SwordAttackCheckInterface.h"
#include "RWCharacterAIEnemyMelee.generated.h"

class AAIControllerEnemyMelee;
class URWAIBehaviorComponent;

UCLASS()
class ROSEWAR_API ARWCharacterAIEnemyMelee : public ARWCharacterAIEnemy, public ISwordAttackCheckInterface
{
	GENERATED_BODY()
	
public:
	ARWCharacterAIEnemyMelee();

	/* IAIInterface Implement */
	virtual void AttackByAI() override;

	/* IClassIdentifierInterface Implement */
	virtual FName SetupClassName() override { return ClassName; }

	/* ISwordAttackCheckInterface Implement */
	virtual class USkeletalMeshComponent* GetSwordBone() override;

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
	AAIControllerEnemyMelee* GetMyController();

/* Component */
private:
	UPROPERTY(VisibleAnywhere, Category = "Animation")
	TObjectPtr<URWAIBehaviorComponent> BehaviorComp;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<USkeletalMeshComponent> LeftWeaponSocketComp;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<USkeletalMeshComponent> RightWeaponSocketComp;

/* Test */
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMesh> WeaponMesh;
};
