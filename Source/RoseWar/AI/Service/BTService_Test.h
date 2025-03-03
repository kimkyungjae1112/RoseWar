// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Test.generated.h"

UCLASS()
class ROSEWAR_API UBTService_Test : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_Test();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
