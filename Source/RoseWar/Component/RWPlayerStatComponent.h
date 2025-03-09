// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/RWStatComponent.h"
#include "Data/RWRoguelikeGameData.h"
#include "RWPlayerStatComponent.generated.h"

UCLASS()
class ROSEWAR_API URWPlayerStatComponent : public URWStatComponent
{
	GENERATED_BODY()
	
public:
	URWPlayerStatComponent();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE FRWRoguelikeGameData GetRoguelikeGameData() const { return RoguelikeGameData; }
	FORCEINLINE void SetCurrentMoney(float InMoney) { CurrentMoney += InMoney; }
	FORCEINLINE float GetCurrentMoney() const { return CurrentMoney; }
	void SetStageLevel(int32 InStageLevel);

/* Data */
private:
	UPROPERTY(VisibleInstanceOnly, Category = "Data", Meta = (AllowPrivateAccess = "true"))
	FRWRoguelikeGameData RoguelikeGameData;

	float CurrentMoney = 100.f;
};
