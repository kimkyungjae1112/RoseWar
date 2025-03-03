// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RWGameInstance.h"
#include "AI/Controller/AIControllerFriendlyBase.h"
#include "AI/Controller/AIControllerEnemyBase.h"
#include "Data/RWGameSingleton.h"

URWGameInstance::URWGameInstance()
{
}

void URWGameInstance::Shutdown()
{
	Super::Shutdown();

	AAIControllerFriendlyBase::ShutdownGame();
	AAIControllerEnemyBase::ShutdownGame();
	URWGameSingleton::Get().InitializeHealth();
}
