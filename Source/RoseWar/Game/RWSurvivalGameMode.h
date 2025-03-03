// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/RWInGameModeBase.h"
#include "RWSurvivalGameMode.generated.h"

UCLASS()
class ROSEWAR_API ARWSurvivalGameMode : public ARWInGameModeBase
{
	GENERATED_BODY()
	
public:
	ARWSurvivalGameMode();
	virtual void PawnKilled(APawn* PawnKilled) override;

private:
	void EndGame(bool bIsPlayerWinner);
};
