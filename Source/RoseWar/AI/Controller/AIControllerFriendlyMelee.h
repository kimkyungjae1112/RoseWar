// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Controller/AIControllerFriendlyBase.h"
#include "AIControllerFriendlyMelee.generated.h"

UCLASS()
class ROSEWAR_API AAIControllerFriendlyMelee : public AAIControllerFriendlyBase
{
	GENERATED_BODY()
	
public:
	AAIControllerFriendlyMelee();

	virtual int32 GetSpawnOrder() const override;

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	virtual void ReciveAttackCommand() override;
	virtual void ReciveRetreatCommand() override;
	virtual void ReciveRestCommand() override;


};
