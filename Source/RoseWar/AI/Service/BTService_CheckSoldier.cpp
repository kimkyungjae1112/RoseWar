// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTService_CheckSoldier.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Data/RWGameSingleton.h"

UBTService_CheckSoldier::UBTService_CheckSoldier()
{
	NodeName = TEXT("Check Soldier");
	Interval = 1.f;
}

void UBTService_CheckSoldier::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	float TotalMaxHp = URWGameSingleton::Get().GetTotalMaxAIEnemyHealth();
	float TotalCurrentHp = URWGameSingleton::Get().GetTotalCurrentAIEnemyHealth();

	if (TotalCurrentHp / TotalMaxHp <= 0.7f)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("RetreatCommand"), true);
	}

}
