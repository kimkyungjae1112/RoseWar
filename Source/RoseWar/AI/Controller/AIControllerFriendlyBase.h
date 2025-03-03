// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Controller/AIControllerBase.h"
#include "Interface/SoldierInterface.h"
#include "AIControllerFriendlyBase.generated.h"

UCLASS()
class ROSEWAR_API AAIControllerFriendlyBase : public AAIControllerBase, public ISoldierInterface
{
	GENERATED_BODY()
	
public:
	static FORCEINLINE void ShutdownGame() { SpawnOrder = 0; }
	virtual int32 GetSpawnOrder() const override { return EachSpawnOrder; }

protected:
	virtual void BeginPlay() override;

	/* Command Ability */
	virtual void ReciveAttackCommand();
	virtual void ReciveRetreatCommand();
	virtual void ReciveRestCommand();

protected:
	static int32 SpawnOrder;
	int32 EachSpawnOrder = 0;
};
