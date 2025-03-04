// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/AIControllerFriendlyBase.h"
#include "Character/RWCharacterBase.h"
#include "Interface/ReadyForBattleInterface.h"

int32 AAIControllerFriendlyBase::SpawnOrder = 0;

void AAIControllerFriendlyBase::BeginPlay()
{
	Super::BeginPlay();

	ARWCharacterBase::OnWarinessCommand.AddUObject(this, &AAIControllerFriendlyBase::ReciveWarinessCommand);
	ARWCharacterBase::OnAttackCommand.AddUObject(this, &AAIControllerFriendlyBase::ReciveAttackCommand);
	ARWCharacterBase::OnRetreatCommand.AddUObject(this, &AAIControllerFriendlyBase::ReciveRetreatCommand);
	ARWCharacterBase::OnRestCommand.AddUObject(this, &AAIControllerFriendlyBase::ReciveRestCommand);
}

void AAIControllerFriendlyBase::ReciveWarinessCommand()
{
	IReadyForBattleInterface* Interface = Cast<IReadyForBattleInterface>(GetPawn());
	if (Interface)
	{
		Interface->ReadyForBattle();
	}
}

void AAIControllerFriendlyBase::ReciveAttackCommand()
{
}

void AAIControllerFriendlyBase::ReciveRetreatCommand()
{
}

void AAIControllerFriendlyBase::ReciveRestCommand()
{
	IReadyForBattleInterface* Interface = Cast<IReadyForBattleInterface>(GetPawn());
	if (Interface)
	{
		Interface->ReadyForRest();
	}
}
