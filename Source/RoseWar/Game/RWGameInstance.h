// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RWGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ROSEWAR_API URWGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	URWGameInstance();

	virtual void Shutdown() override;
};
