// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ReadyForBattleInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UReadyForBattleInterface : public UInterface
{
	GENERATED_BODY()
};

class ROSEWAR_API IReadyForBattleInterface
{
	GENERATED_BODY()

public:
	virtual void ReadyForBattle() = 0;
	virtual void ReadyForRest() = 0;
};
