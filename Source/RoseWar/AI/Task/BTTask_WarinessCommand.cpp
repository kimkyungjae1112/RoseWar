// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_WarinessCommand.h"
#include "AIController.h"
#include "Interface/EnemyCommanderInterface.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_WarinessCommand::UBTTask_WarinessCommand()
{
	NodeName = TEXT("WarinessCommand");
}

EBTNodeResult::Type UBTTask_WarinessCommand::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (OwnerPawn == nullptr) return EBTNodeResult::Failed;

	IEnemyCommanderInterface* Interface = Cast<IEnemyCommanderInterface>(OwnerPawn);
	if (Interface == nullptr) return EBTNodeResult::Failed;

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("WarinessCommand"), true);

	Interface->EnemyWarinessCommand();

	return EBTNodeResult::Succeeded;
}
