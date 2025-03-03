// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_AttackCommand.generated.h"

UCLASS()
class ROSEWAR_API UBTTask_AttackCommand : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_AttackCommand();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
