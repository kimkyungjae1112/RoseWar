// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RWPlayerState.h"
#include "Data/RWGameSingleton.h"

ARWPlayerState::ARWPlayerState()
{
}

void ARWPlayerState::BeginPlay()
{
	Super::BeginPlay();

	SetStageLevel(1);
	CurrentMoney = RoguelikeGameData.Money;
}

void ARWPlayerState::SetStageLevel(int32 InStageLevel)
{
	RoguelikeGameData = URWGameSingleton::Get().GetRoguelikeGameData(InStageLevel);
	check(RoguelikeGameData.Money > 0.f);
}
