// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/AIControllerEnemyRanged.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "RoseWar.h"

AAIControllerEnemyRanged::AAIControllerEnemyRanged()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBDataRef(TEXT("/Script/AIModule.BlackboardData'/Game/AI/BB_EnemyRanged.BB_EnemyRanged'"));
	if (BBDataRef.Object)
	{
		BBData = BBDataRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTDataRef(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/BT_EnemyRanged.BT_EnemyRanged'"));
	if (BTDataRef.Object)
	{
		BTData = BTDataRef.Object;
	}

	// Sight 설정
	UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 1500.0f;
	SightConfig->LoseSightRadius = 1600.0f;
	SightConfig->PeripheralVisionAngleDegrees = 270.0f;
	SightConfig->SetMaxAge(5.0f);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	PerceptionComp->ConfigureSense(*SightConfig);
	PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
	PerceptionComp->OnPerceptionUpdated.AddDynamic(this, &AAIControllerEnemyRanged::OnPerceptionUpdated);

	SetPerceptionComponent(*PerceptionComp);

	TeamID = FGenericTeamId(1);
}

int32 AAIControllerEnemyRanged::GetSpawnOrder() const
{
	return EachSpawnOrder;
}

void AAIControllerEnemyRanged::BeginPlay()
{
	Super::BeginPlay();
}

void AAIControllerEnemyRanged::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	SpawnOrder++;
	EachSpawnOrder = SpawnOrder;
	RW_LOG(LogRoseWar, Log, TEXT("Spawn Order : %d"), EachSpawnOrder);
}

void AAIControllerEnemyRanged::ReciveEnemyWarinessCommand()
{
	Super::ReciveEnemyWarinessCommand();
}

void AAIControllerEnemyRanged::ReciveEnemyAttackCommand()
{
	Super::ReciveEnemyAttackCommand();

	GetBlackboardComponent()->SetValueAsBool(TEXT("ReciveCommand"), true);
	GetBlackboardComponent()->SetValueAsBool(TEXT("AttackCommand"), true);
}

void AAIControllerEnemyRanged::ReciveEnemyRetreatCommand()
{
	Super::ReciveEnemyRetreatCommand();
}

void AAIControllerEnemyRanged::ReciveEnemyRestCommand()
{
	Super::ReciveEnemyRestCommand();
}

void AAIControllerEnemyRanged::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	for (AActor* Actor : UpdatedActors)
	{
		ETeamAttitude::Type Attitude = GetTeamAttitudeTowards(*Actor);
		if (Attitude == ETeamAttitude::Hostile)
		{
			APawn* PossessedPawn = GetPawn();
			if (PossessedPawn)
			{
				GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), Cast<APawn>(Actor));
			}
		}
		else if (Attitude == ETeamAttitude::Friendly)
		{
			if (Actor->ActorHasTag(TEXT("Commander")))
			{
				GetBlackboardComponent()->SetValueAsObject(TEXT("Commander"), Cast<APawn>(Actor));
			}
		}
	}
}
