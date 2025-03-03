// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/AIControllerEnemyMelee.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "RoseWar.h"
#include "Character/RWCharacterAIEnemy.h"
#include "Data/RWGameSingleton.h"

AAIControllerEnemyMelee::AAIControllerEnemyMelee()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBDataRef(TEXT("/Script/AIModule.BlackboardData'/Game/AI/BB_EnemyMelee.BB_EnemyMelee'"));
	if (BBDataRef.Object)
	{
		BBData = BBDataRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTDataRef(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/BT_EnemyMelee.BT_EnemyMelee'"));
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
	PerceptionComp->OnPerceptionUpdated.AddDynamic(this, &AAIControllerEnemyMelee::OnPerceptionUpdated);

	SetPerceptionComponent(*PerceptionComp);

	TeamID = FGenericTeamId(1);
}

int32 AAIControllerEnemyMelee::GetSpawnOrder() const
{
	return EachSpawnOrder;
}

void AAIControllerEnemyMelee::BeginPlay()
{
	Super::BeginPlay();

}

void AAIControllerEnemyMelee::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	SpawnOrder++;
	EachSpawnOrder = SpawnOrder;
	RW_LOG(LogRoseWar, Log, TEXT("Spawn Order : %d"), EachSpawnOrder);
}

void AAIControllerEnemyMelee::ReciveEnemyWarinessCommand()
{
	Super::ReciveEnemyWarinessCommand();
}

void AAIControllerEnemyMelee::ReciveEnemyAttackCommand()
{
	Super::ReciveEnemyAttackCommand();

	GetBlackboardComponent()->SetValueAsBool(TEXT("ReciveCommand"), true);
	GetBlackboardComponent()->SetValueAsBool(TEXT("AttackCommand"), true);
}

void AAIControllerEnemyMelee::ReciveEnemyRetreatCommand()
{
	Super::ReciveEnemyRetreatCommand();

	GetBlackboardComponent()->SetValueAsBool(TEXT("ReciveCommand"), false);
	GetBlackboardComponent()->SetValueAsBool(TEXT("AttackCommand"), false);
}

void AAIControllerEnemyMelee::ReciveEnemyRestCommand()
{
	Super::ReciveEnemyRestCommand();
}

void AAIControllerEnemyMelee::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
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
		else if (Attitude == ETeamAttitude::Friendly && !GetBlackboardComponent()->GetValueAsObject(TEXT("Commander")))
		{
			if (Actor->ActorHasTag(TEXT("Commander")))
			{
				GetBlackboardComponent()->SetValueAsObject(TEXT("Commander"), Cast<APawn>(Actor));
				URWGameSingleton::Get().RegisterEnemy(Cast<ARWCharacterAIEnemy>(GetPawn()));
			}
		}
	}
}