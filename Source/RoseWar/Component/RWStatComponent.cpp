// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/RWStatComponent.h"
#include "Data/RWGameSingleton.h"
#include "Interface/ClassIdentifierInterface.h"
#include "RoseWar.h"

URWStatComponent::URWStatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void URWStatComponent::BeginPlay()
{
	Super::BeginPlay();

	IClassIdentifierInterface* CII = Cast<IClassIdentifierInterface>(GetOwner());
	if (CII)
	{
		SetStat(CII->SetupClassName());
		CurrentHp = BaseStat.MaxHp;
	}
}

void URWStatComponent::SetStat(const FName& InName)
{
	BaseStat = URWGameSingleton::Get().GetCharacterStat(InName);
	check(BaseStat.MaxHp > 0.f);
}

float URWStatComponent::ApplyDamage(float InDamage)
{
	const float ActualDamage = FMath::Clamp(InDamage, 0, InDamage);
	const float PrevHp = CurrentHp;

	SetHp(PrevHp - ActualDamage);
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}

	return 0.0f;
}

void URWStatComponent::SetHp(float NewHp)
{
	CurrentHp = NewHp;
	OnHpChanged.Broadcast(CurrentHp);
	//RW_LOG(LogRoseWar, Log, TEXT("Remain Health : %f"), CurrentHp);
}

void URWStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

