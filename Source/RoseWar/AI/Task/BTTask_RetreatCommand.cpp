// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_RetreatCommand.h"
#include "AIController.h"
#include "Interface/EnemyCommanderInterface.h"

UBTTask_RetreatCommand::UBTTask_RetreatCommand()
{
	NodeName = TEXT("AttackCommand");
}

EBTNodeResult::Type UBTTask_RetreatCommand::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (OwnerPawn == nullptr) return EBTNodeResult::Failed;

	IEnemyCommanderInterface* Interface = Cast<IEnemyCommanderInterface>(OwnerPawn);
	if (Interface == nullptr) return EBTNodeResult::Failed;

	Interface->EnemyRetreatCommand();

	return EBTNodeResult::Succeeded;
}

