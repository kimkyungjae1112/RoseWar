// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RWDeathMatchGameMode.h"
#include "RoseWar.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "UI/DeathMatchGameWidget.h"
#include "EngineUtils.h"
#include "AI/Controller/AIControllerEnemyCommander.h"

ARWDeathMatchGameMode::ARWDeathMatchGameMode()
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

	static ConstructorHelpers::FClassFinder<UDeathMatchGameWidget> DeathMatchWidgetClassRef(TEXT("/Game/UI/WBP_DeathMatchGame.WBP_DeathMatchGame_C"));
	if (DeathMatchWidgetClassRef.Succeeded())
	{
		DeathMatchWidgetClass = DeathMatchWidgetClassRef.Class;
	}
}

void ARWDeathMatchGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerController* PC = Cast<APlayerController>(PawnKilled->GetController());
	if (PC != nullptr)
	{
		IncrementBlueScore();
	}

	for (AAIControllerEnemyCommander* AIController : TActorRange<AAIControllerEnemyCommander>(GetWorld()))
	{
		if (AIController->IsDead())
		{
			IncrementRedScore();
		}
	}
}

void ARWDeathMatchGameMode::EnterGame()
{
	Super::EnterGame();

	DeathMatchWidget = CreateWidget<UDeathMatchGameWidget>(GetWorld(), DeathMatchWidgetClass);
	if (DeathMatchWidget)
	{
		DeathMatchWidget->AddToViewport();
	}
}

void ARWDeathMatchGameMode::BeginPlay()
{
	Super::BeginPlay();

	EnterGame();

	FTimerHandle TimeLimitHandle;
	GetWorld()->GetTimerManager().SetTimer(TimeLimitHandle, this, &ARWDeathMatchGameMode::DecreaseTimeLimit, 0.1f, true);
}

void ARWDeathMatchGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}

void ARWDeathMatchGameMode::IncrementRedScore()
{
	RedTeamPoint++;
	DeathMatchWidget->ChangeRedScore(FString::Printf(TEXT("%d"), RedTeamPoint));
}

void ARWDeathMatchGameMode::IncrementBlueScore()
{
	BlueTeamPoint++;
	DeathMatchWidget->ChangeRedScore(FString::Printf(TEXT("%d"), BlueTeamPoint));
}

void ARWDeathMatchGameMode::DecreaseTimeLimit()
{
	TimeLimit -= 0.1f;
	DeathMatchWidget->ChangeTimeLimit(FString::Printf(TEXT("%f.1"), TimeLimit));

	if (TimeLimit < KINDA_SMALL_NUMBER)
	{
		EndGame(RedTeamPoint > BlueTeamPoint);
	}
}
