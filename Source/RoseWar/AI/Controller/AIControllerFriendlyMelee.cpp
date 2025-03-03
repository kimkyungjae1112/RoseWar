// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/AIControllerFriendlyMelee.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "RoseWar.h"

AAIControllerFriendlyMelee::AAIControllerFriendlyMelee()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBDataRef(TEXT("/Script/AIModule.BlackboardData'/Game/AI/BB_FriendlyMelee.BB_FriendlyMelee'"));
	if (BBDataRef.Object)
	{
		BBData = BBDataRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTDataRef(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/BT_FriendlyMelee.BT_FriendlyMelee'"));
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
	PerceptionComp->OnPerceptionUpdated.AddDynamic(this, &AAIControllerFriendlyMelee::OnPerceptionUpdated);

	SetPerceptionComponent(*PerceptionComp);

	TeamID = FGenericTeamId(0);
}

int32 AAIControllerFriendlyMelee::GetSpawnOrder() const
{
	return EachSpawnOrder;
}

void AAIControllerFriendlyMelee::BeginPlay()
{
	Super::BeginPlay();

}

void AAIControllerFriendlyMelee::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	SpawnOrder++;
	EachSpawnOrder = SpawnOrder;
	RW_LOG(LogRoseWar, Log, TEXT("Spawn Order : %d"), EachSpawnOrder);
}

void AAIControllerFriendlyMelee::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	for (AActor* Actor : UpdatedActors)
	{
		ETeamAttitude::Type Attitude = GetTeamAttitudeTowards(*Actor);
		if (Attitude == ETeamAttitude::Hostile)
		{
			//UE_LOG(LogTemp, Log, TEXT("Detected enemy: %s"), *Actor->GetName());
			APawn* PossessedPawn = GetPawn();
			if (PossessedPawn)
			{
				/*float Distance = FVector::Dist(Actor->GetActorLocation(), PossessedPawn->GetActorLocation());
				if (MinDistance > Distance)
				{
					MinDistance = Distance;
					GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), Cast<APawn>(Actor));
				}*/

				GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), Cast<APawn>(Actor));
			}
		}
		else if (Attitude == ETeamAttitude::Friendly)
		{
			//UE_LOG(LogTemp, Log, TEXT("Detected friendly: %s"), *Actor->GetName());
			if (Actor->ActorHasTag(TEXT("Commander")))
			{
				GetBlackboardComponent()->SetValueAsObject(TEXT("Commander"), Cast<APawn>(Actor));
			}
		}
	}
}

void AAIControllerFriendlyMelee::ReciveAttackCommand()
{
	GetBlackboardComponent()->SetValueAsBool(TEXT("ReciveCommand"), true);
	GetBlackboardComponent()->SetValueAsBool(TEXT("AttackCommand"), true);
}

void AAIControllerFriendlyMelee::ReciveRetreatCommand()
{
	GetBlackboardComponent()->SetValueAsBool(TEXT("ReciveCommand"), false);
	GetBlackboardComponent()->SetValueAsBool(TEXT("AttackCommand"), false);
}

void AAIControllerFriendlyMelee::ReciveRestCommand()
{
}
