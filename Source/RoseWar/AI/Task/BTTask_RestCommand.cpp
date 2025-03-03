// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_RestCommand.h"
#include "AIController.h"
#include "Interface/EnemyCommanderInterface.h"

UBTTask_RestCommand::UBTTask_RestCommand()
{
	NodeName = TEXT("Rest Command");
}

EBTNodeResult::Type UBTTask_RestCommand::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (OwnerPawn == nullptr) return EBTNodeResult::Failed;

	IEnemyCommanderInterface* Interface = Cast<IEnemyCommanderInterface>(OwnerPawn);
	if (Interface == nullptr) return EBTNodeResult::Failed;

	Interface->EnemyRestCommand();

	return EBTNodeResult::Succeeded;
}
