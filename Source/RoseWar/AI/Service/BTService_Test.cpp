// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTService_Test.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_Test::UBTService_Test()
{
	NodeName = TEXT("FindToTest");
	Interval = 0.8f;
}

void UBTService_Test::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UE_LOG(LogTemp, Display, TEXT("Tick Node"));
	APawn* Owner = OwnerComp.GetAIOwner()->GetPawn();
	if (Owner == nullptr) return;

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor")));
	if (Target == nullptr) return;

	UE_LOG(LogTemp, Display, TEXT("Target Is Set"));
	float Dist = FVector::Dist(Owner->GetActorLocation(), Target->GetActorLocation());
	if (Dist <= 600.f)
	{
		UE_LOG(LogTemp, Display, TEXT("Attack Command True"));
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("AttackCommand"), true);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("WarinessCommand"), false);
	}
	else if (Dist <= 1500.f)
	{
		UE_LOG(LogTemp, Display, TEXT("Wariness Command True"));
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("AttackCommand"), false);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("WarinessCommand"), true);
	}
}
