// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RWCharacterBase.h"
#include "Interface/AIInterface.h"
#include "Interface/HpBarInterface.h"
#include "RWCharacterAIBase.generated.h"

class UHpBarWidgetComponent;
class UHpBarBaseWidget;
class UHpBarWidget;
class URWStatComponent;

UCLASS()
class ROSEWAR_API ARWCharacterAIBase : public ARWCharacterBase, public IAIInterface, public IHpBarInterface
{
	GENERATED_BODY()
	
public:
	ARWCharacterAIBase();

protected:
	virtual void BeginPlay() override;

/* IAIInterface Implement */
public:
	virtual void SetAttackFinishedDelegate(const FOnAttackFinished& InOnAttackFinished) override;

	virtual void AttackByAI() override;

	virtual float GetAttackRange() override;
	virtual float GetTurnSpeed() override;

/* IHpBarInterface Implement */
public:
	virtual void SetupHpBarWidget(class UHpBarWidget* InHpBarWidget) override;

/* Damaged */
public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	bool CheckDeath() const;

/* Ability */
protected:
	virtual void SetDead();

	/* Attack Ability */
	FOnAttackFinished OnAttackFinished;

/* UI */
protected:
	UPROPERTY(VisibleAnywhere, Category = "UI")
	TObjectPtr<UHpBarWidgetComponent> HpBarComp;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TSubclassOf<UHpBarBaseWidget> HpBarBaseWidget;

/* Stat */
protected:
	UPROPERTY(VisibleAnywhere, Category = "Stat")
	TObjectPtr<URWStatComponent> StatComp;

/* Particle */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UNiagaraComponent> NiagaraComp;

	virtual void RunParticle();

};
