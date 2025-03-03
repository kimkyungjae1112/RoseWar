// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyCommanderInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyCommanderInterface : public UInterface
{
	GENERATED_BODY()
};

class ROSEWAR_API IEnemyCommanderInterface
{
	GENERATED_BODY()

public:
	virtual void EnemyWarinessCommand() = 0;
	virtual void EnemyAttackCommand() = 0;
	virtual void EnemyRetreatCommand() = 0;
	virtual void EnemyRestCommand() = 0;
};
