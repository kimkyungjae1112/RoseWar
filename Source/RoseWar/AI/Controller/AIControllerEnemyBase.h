// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Controller/AIControllerBase.h"
#include "Interface/SoldierInterface.h"
#include "AIControllerEnemyBase.generated.h"

UCLASS()
class ROSEWAR_API AAIControllerEnemyBase : public AAIControllerBase, public ISoldierInterface
{
	GENERATED_BODY()
	
public:
	AAIControllerEnemyBase();

public:
	static FORCEINLINE void ShutdownGame() { SpawnOrder = 0; }
	virtual int32 GetSpawnOrder() const override { return EachSpawnOrder; }

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	virtual void ReciveEnemyWarinessCommand();
	virtual void ReciveEnemyAttackCommand();
	virtual void ReciveEnemyRetreatCommand();
	virtual void ReciveEnemyRestCommand();

protected:
	static int32 SpawnOrder;
	int32 EachSpawnOrder = 0;
};
