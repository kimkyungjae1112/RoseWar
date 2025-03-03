// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RWSurvivalGameMode.h"
#include "GameFramework/PlayerController.h"
#include "EngineUtils.h"
#include "AI/Controller/AIControllerEnemyCommander.h"

ARWSurvivalGameMode::ARWSurvivalGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Game/Blueprints/Player/BP_RWCharactePlayer.BP_RWCharactePlayer_C"));
	if (DefaultPawnClassRef.Succeeded())
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/CoreUObject.Class'/Script/RoseWar.RWPlayerController'"));
	if (PlayerControllerClassRef.Succeeded())
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}

void ARWSurvivalGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerController* PC = Cast<APlayerController>(PawnKilled->GetController());
	if (PC != nullptr)
	{
		EndGame(false);
	}

	for (AAIControllerEnemyCommander* AIController : TActorRange<AAIControllerEnemyCommander>(GetWorld()))
	{
		if (!AIController->IsDead())
		{
			return;
		}
	}
	EndGame(true);
}

void ARWSurvivalGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}