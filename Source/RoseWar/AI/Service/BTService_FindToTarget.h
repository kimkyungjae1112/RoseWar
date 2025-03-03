// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_FindToTarget.generated.h"

UCLASS()
class ROSEWAR_API UBTService_FindToTarget : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_FindToTarget();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
