// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SwordAttackCheckInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USwordAttackCheckInterface : public UInterface
{
	GENERATED_BODY()
};

class ROSEWAR_API ISwordAttackCheckInterface
{
	GENERATED_BODY()

public:
	virtual class USkeletalMeshComponent* GetSwordBone() = 0;
};
