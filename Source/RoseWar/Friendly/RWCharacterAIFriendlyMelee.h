// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RWCharacterAIFriendly.h"
#include "Interface/SwordAttackCheckInterface.h"
#include "RWCharacterAIFriendlyMelee.generated.h"

class AAIControllerFriendlyMelee;
class URWAIBehaviorComponent;

UCLASS()
class ROSEWAR_API ARWCharacterAIFriendlyMelee : public ARWCharacterAIFriendly, public ISwordAttackCheckInterface
{
	GENERATED_BODY()
	
public:
	ARWCharacterAIFriendlyMelee();

	/* IAIInterface Implement */
	virtual void AttackByAI() override;

	/* IClassIdentifierInterface Implement */
	virtual FName SetupClassName() override { return ClassName; }

	/* Damaged */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	/* ISwordAttackCheckInterface Implement */
	virtual class USkeletalMeshComponent* GetSwordBone() override;

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
	AAIControllerFriendlyMelee* GetMyController();

/* Component */
private:
	UPROPERTY(VisibleAnywhere, Category = "Animation")
	TObjectPtr<URWAIBehaviorComponent> BehaviorComp;

};
