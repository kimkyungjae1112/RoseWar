// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GenericTeamAgentInterface.h"
#include "AIControllerBase.generated.h"

class UBlackboardData;
class UBehaviorTree;
class UAIPerceptionComponent;

UCLASS()
class ROSEWAR_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()
	
public:
	AAIControllerBase();

	void RunAI();
	void StopAI();

protected:
	virtual void OnPossess(APawn* InPawn) override;

	/* IGenericTeamAgentInterface Implement */
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAIPerceptionComponent> PerceptionComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBlackboardData> BBData;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBehaviorTree> BTData;

	FGenericTeamId TeamID;
};
