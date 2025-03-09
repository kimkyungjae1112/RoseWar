// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/RWPlayerStatComponent.h"
#include "Data/RWGameSingleton.h"

URWPlayerStatComponent::URWPlayerStatComponent()
{
}

void URWPlayerStatComponent::BeginPlay()
{
	Super::BeginPlay();

}

void URWPlayerStatComponent::SetStageLevel(int32 InStageLevel)
{
	RoguelikeGameData = URWGameSingleton::Get().GetRoguelikeGameData(InStageLevel);
}
