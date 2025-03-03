// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_FollowCommander.generated.h"

UCLASS()
class ROSEWAR_API UBTService_FollowCommander : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_FollowCommander();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
