// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_WarinessCommand.generated.h"

UCLASS()
class ROSEWAR_API UBTTask_WarinessCommand : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_WarinessCommand();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
