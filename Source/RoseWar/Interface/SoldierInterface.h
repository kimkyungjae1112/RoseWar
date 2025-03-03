// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SoldierInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USoldierInterface : public UInterface
{
	GENERATED_BODY()
};

class ROSEWAR_API ISoldierInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetSpawnOrder() const = 0;
};
