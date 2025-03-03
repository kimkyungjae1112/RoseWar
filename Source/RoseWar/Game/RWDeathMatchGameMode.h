// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/RWInGameModeBase.h"
#include "RWDeathMatchGameMode.generated.h"

class UUserWidget;
class UTextBlock;
class UDeathMatchGameWidget;

UCLASS()
class ROSEWAR_API ARWDeathMatchGameMode : public ARWInGameModeBase
{
	GENERATED_BODY()

public:
	ARWDeathMatchGameMode();
	virtual void PawnKilled(APawn* PawnKilled) override;
	virtual void EnterGame() override;

protected:
	virtual void BeginPlay() override;

private:
	void EndGame(bool bIsPlayerWinner);
	void IncrementRedScore();
	void IncrementBlueScore();

	UFUNCTION()
	void DecreaseTimeLimit();

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDeathMatchGameWidget> DeathMatchWidget;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<UDeathMatchGameWidget> DeathMatchWidgetClass;

	int32 RedTeamPoint = 0;
	int32 BlueTeamPoint = 0;
	float TimeLimit = 30.f;
};
