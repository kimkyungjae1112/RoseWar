// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RetreatCommand.generated.h"

UCLASS()
class ROSEWAR_API UBTTask_RetreatCommand : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_RetreatCommand();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
