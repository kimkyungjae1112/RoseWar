// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RWComboAttackData.generated.h"

UCLASS()
class ROSEWAR_API URWComboAttackData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Frame")
	TArray<float> EffectiveFrameCount;

	UPROPERTY(EditAnywhere, Category = "Name")
	FString SectionName;

	UPROPERTY(EditAnywhere, Category = "Name")
	float FrameRate;

	UPROPERTY(EditAnywhere, Category = "Combo")
	int32 MaxCombo;
};
