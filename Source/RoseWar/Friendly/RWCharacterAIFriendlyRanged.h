// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RWCharacterAIFriendly.h"
#include "Interface/BowAttackCheckInterface.h"
#include "RWCharacterAIFriendlyRanged.generated.h"

class AAIControllerFriendlyRanged;
class URWAIBehaviorComponent;

UCLASS()
class ROSEWAR_API ARWCharacterAIFriendlyRanged : public ARWCharacterAIFriendly, public IBowAttackCheckInterface
{
	GENERATED_BODY()

public:
	ARWCharacterAIFriendlyRanged();

	/* IAIInterface Implement */
	virtual void AttackByAI() override;
	virtual float GetAttackRange() override;

	/* IClassIdentifierInterface Implement */
	virtual FName SetupClassName() override { return ClassName; }

	/* IBowAttackCheckInterface Implement */
	virtual void CreateArrow() override;
	virtual void ReleaseArrow() override;

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
	AAIControllerFriendlyRanged* GetMyController();

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
