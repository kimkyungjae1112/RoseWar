// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/RWInGameModeBase.h"
#include "RWRougeGameMode.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextStage)

UCLASS()
class ROSEWAR_API ARWRougeGameMode: public ARWInGameModeBase
{
	GENERATED_BODY()
	
public:
	ARWRougeGameMode();
	virtual void PawnKilled(APawn* PawnKilled) override;

protected:
	virtual void BeginPlay() override;

public:
	FOnNextStage OnNextStage;

private:
	void EndGame(bool bIsPlayerWinner);
	void NextStage();

	int32 SpawnEnemyNum = 0;
	int32 CurrentLevel = 1;
};
