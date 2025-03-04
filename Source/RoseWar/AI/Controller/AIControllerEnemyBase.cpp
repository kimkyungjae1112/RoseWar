// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/AIControllerEnemyBase.h"
#include "Character/RWCharacterAIEnemy.h"
#include "Interface/ReadyForBattleInterface.h"
#include "RoseWar.h"

int32 AAIControllerEnemyBase::SpawnOrder = 0;

AAIControllerEnemyBase::AAIControllerEnemyBase()
{
}

void AAIControllerEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	ARWCharacterAIEnemy::OnEnemyWarinessCommand.AddUObject(this, &AAIControllerEnemyBase::ReciveEnemyWarinessCommand);
	ARWCharacterAIEnemy::OnEnemyAttackCommand.AddUObject(this, &AAIControllerEnemyBase::ReciveEnemyAttackCommand);
	ARWCharacterAIEnemy::OnEnemyRetreatCommand.AddUObject(this, &AAIControllerEnemyBase::ReciveEnemyRetreatCommand);
	ARWCharacterAIEnemy::OnEnemyRestCommand.AddUObject(this, &AAIControllerEnemyBase::ReciveEnemyRestCommand);
}

void AAIControllerEnemyBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}

void AAIControllerEnemyBase::ReciveEnemyWarinessCommand()
{
	IReadyForBattleInterface* Interface = Cast<IReadyForBattleInterface>(GetPawn());
	if (Interface)
	{
		Interface->ReadyForBattle();
	}
}

void AAIControllerEnemyBase::ReciveEnemyAttackCommand()
{
}

void AAIControllerEnemyBase::ReciveEnemyRetreatCommand()
{
}

void AAIControllerEnemyBase::ReciveEnemyRestCommand()
{
	IReadyForBattleInterface* Interface = Cast<IReadyForBattleInterface>(GetPawn());
	if (Interface)
	{
		Interface->ReadyForRest();
	}
}

