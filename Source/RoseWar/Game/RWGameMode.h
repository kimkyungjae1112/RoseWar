// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RWGameMode.generated.h"

UCLASS()
class ROSEWAR_API ARWGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARWGameMode();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UMainMenuWidget> MainMenuPtr;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class UMainMenuWidget> MainMenuClass;

	
};
