// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTService_FollowCommander.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/SoldierInterface.h"

UBTService_FollowCommander::UBTService_FollowCommander()
{
	NodeName = TEXT("Service_FollowCommander");
	Interval = 0.1f;
}

void UBTService_FollowCommander::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (OwnerPawn == nullptr) return;

	APawn* CommanderPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Commander")));
	if (CommanderPawn == nullptr) return;

	ISoldierInterface* Interface = Cast<ISoldierInterface>(OwnerPawn->GetController());
	if (Interface == nullptr) return;

	OwnerPawn->SetActorRotation(FMath::RInterpTo(OwnerPawn->GetActorRotation(), CommanderPawn->GetActorForwardVector().Rotation(), DeltaSeconds, 2.f));

	FRotator CommanderRotation = CommanderPawn->GetActorRotation();
	FRotator CommanderRotationYaw(0.f, CommanderRotation.Yaw, 0.f); 

	FVector Forward = FRotationMatrix(CommanderRotation).GetScaledAxis(EAxis::X);
	FVector Right = FRotationMatrix(CommanderRotation).GetScaledAxis(EAxis::Y);

	float Distance = 200.f;
	FVector InitLocation = (CommanderPawn->GetActorLocation() - (Forward * Distance)) - FVector(0.f, -150.f, 0.f);
	//UE_LOG(LogTemp, Display, TEXT("InitLocation : %s"), *InitLocation.ToString());

	const int32 Row = 3;
	const int32 Column = 3;

	int32 MyRow = (Interface->GetSpawnOrder() - 1) / Column;
	int32 MyColumn = Interface->GetSpawnOrder() % Column;
	//UE_LOG(LogTemp, Display, TEXT("[%s] MyRow : %d  /  MyColumn : %d"), *OwnerPawn->GetActorNameOrLabel(), MyRow, MyColumn);

	FVector FollowLocation = InitLocation - (Forward * (MyRow * 150.f)) + (Right * (MyColumn * 150.f));


	//FVector FollowLocation = InitLocation + (FVector(-150.f, 0.f, 0.f) * MyRow) + (FVector(0.f, 150.f, 0.f) * MyColumn);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("FollowLocation"), FollowLocation);

	
}
