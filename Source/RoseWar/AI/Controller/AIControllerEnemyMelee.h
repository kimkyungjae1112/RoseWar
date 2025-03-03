// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Controller/AIControllerEnemyBase.h"
#include "AIControllerEnemyMelee.generated.h"

UCLASS()
class ROSEWAR_API AAIControllerEnemyMelee : public AAIControllerEnemyBase
{
	GENERATED_BODY()

public:
	AAIControllerEnemyMelee();

	virtual int32 GetSpawnOrder() const override;

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	virtual void ReciveEnemyWarinessCommand() override;
	virtual void ReciveEnemyAttackCommand() override;
	virtual void ReciveEnemyRetreatCommand() override;
	virtual void ReciveEnemyRestCommand() override;

private:
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);
	
};
