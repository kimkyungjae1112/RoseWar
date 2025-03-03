// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Controller/AIControllerBase.h"
#include "AIControllerEnemyCommander.generated.h"

UCLASS()
class ROSEWAR_API AAIControllerEnemyCommander : public AAIControllerBase
{
	GENERATED_BODY()

public:
	AAIControllerEnemyCommander();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	bool IsDead() const;

private:
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);



};
