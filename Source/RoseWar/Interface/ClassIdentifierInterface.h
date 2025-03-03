// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ClassIdentifierInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UClassIdentifierInterface : public UInterface
{
	GENERATED_BODY()
};

class ROSEWAR_API IClassIdentifierInterface
{
	GENERATED_BODY()

public:
	virtual FName SetupClassName() = 0;
};
