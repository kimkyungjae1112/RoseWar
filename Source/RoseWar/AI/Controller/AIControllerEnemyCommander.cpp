// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/AIControllerEnemyCommander.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Enemy/RWCharacterAIEnemyCommander.h"
#include "Data/RWGameSingleton.h"

AAIControllerEnemyCommander::AAIControllerEnemyCommander()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBDataRef(TEXT("/Script/AIModule.BlackboardData'/Game/AI/BB_EnemyCommander.BB_EnemyCommander'"));
	if (BBDataRef.Object)
	{
		BBData = BBDataRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTDataRef(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/BT_EnemyCommander.BT_EnemyCommander'"));
	if (BTDataRef.Object)
	{
		BTData = BTDataRef.Object;
	}


	// Sight 설정
	UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 5000.0f;
	SightConfig->LoseSightRadius = 8000.0f;
	SightConfig->PeripheralVisionAngleDegrees = 270.0f;
	SightConfig->SetMaxAge(5.0f);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	PerceptionComp->ConfigureSense(*SightConfig);
	PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
	PerceptionComp->OnPerceptionUpdated.AddDynamic(this, &AAIControllerEnemyCommander::OnPerceptionUpdated);

	SetPerceptionComponent(*PerceptionComp);

	TeamID = FGenericTeamId(1);
}

void AAIControllerEnemyCommander::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle InitTimer;
	GetWorld()->GetTimerManager().SetTimer(InitTimer, [&]()
		{
			URWGameSingleton::Get().RegisterEnemy(Cast<ARWCharacterAIEnemy>(GetPawn()));
		}, 1.f, false);
}

void AAIControllerEnemyCommander::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}

bool AAIControllerEnemyCommander::IsDead() const
{
	ARWCharacterAIEnemyCommander* Commander = Cast<ARWCharacterAIEnemyCommander>(GetPawn());
	if (Commander != nullptr)
	{
		Commander->CheckDeath();
	}
	return true;
}

void AAIControllerEnemyCommander::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
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
		}
	}
}