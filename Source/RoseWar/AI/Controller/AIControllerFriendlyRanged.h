// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Controller/AIControllerFriendlyBase.h"
#include "AIControllerFriendlyRanged.generated.h"

UCLASS()
class ROSEWAR_API AAIControllerFriendlyRanged : public AAIControllerFriendlyBase
{
	GENERATED_BODY()
	
public:
	AAIControllerFriendlyRanged();

	virtual int32 GetSpawnOrder() const override;

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	virtual void ReciveWarinessCommand() override; 
	virtual void ReciveAttackCommand() override;
	virtual void ReciveRetreatCommand() override;
	virtual void ReciveRestCommand() override;
};
