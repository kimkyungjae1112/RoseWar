// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/RWInGameModeBase.h"
#include "RWDominationGameMode.generated.h"

UCLASS()
class ROSEWAR_API ARWDominationGameMode : public ARWInGameModeBase
{
	GENERATED_BODY()
	
public:
	ARWDominationGameMode();
	virtual void PawnKilled(APawn* PawnKilled) override;

private:
	void EndGame(bool bIsPlayerWinner);
};
