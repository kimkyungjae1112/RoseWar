// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTService_FindToTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_FindToTarget::UBTService_FindToTarget()
{
	NodeName = TEXT("FindToTarget");
	Interval = 0.8f;
}

void UBTService_FindToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* Owner = OwnerComp.GetAIOwner()->GetPawn();
	if (Owner == nullptr) return;

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor")));
	if (Target == nullptr) return;
	
	float Dist = FVector::Dist(Owner->GetActorLocation(), Target->GetActorLocation());
	if (Dist <= 2000.f) //공격
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("AttackCommand"), true);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("WarinessCommand"), false);
	}
	else if (Dist <= 8000.f && Dist > 2000.f) //경계
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("AttackCommand"), false);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("WarinessCommand"), true);
	}


	//OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("WarinessCommand"), true);
}
