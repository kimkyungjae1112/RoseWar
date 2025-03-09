// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RWRougeGameMode.h"
#include "Player/RWPlayerController.h"
#include "GameFramework/PlayerState.h"
#include "EngineUtils.h"
#include "AI/Controller/AIControllerEnemyCommander.h"
#include "Kismet/GameplayStatics.h"

ARWRougeGameMode::ARWRougeGameMode() : SpawnEnemyNum(3)
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
	static ConstructorHelpers::FClassFinder<APlayerState> PlayerStateClassRef(TEXT("/Script/CoreUObject.Class'/Script/RoseWar.RWPlayerState'"));
	if (PlayerStateClassRef.Succeeded())
	{
		PlayerStateClass = PlayerStateClassRef.Class;
	}
}

void ARWRougeGameMode::PawnKilled(APawn* PawnKilled)
{
	APlayerController* PC = Cast<APlayerController>(PawnKilled->GetController());
	if (PC != nullptr)
	{
		EndGame(false);
		return;
	}

	for (AAIControllerEnemyCommander* AIController : TActorRange<AAIControllerEnemyCommander>(GetWorld()))
	{
		if (!AIController->IsDead())
		{
			return;
		}
	}
	NextStage();
}

void ARWRougeGameMode::BeginPlay()
{
	Super::BeginPlay();

}

void ARWRougeGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}

void ARWRougeGameMode::NextStage()
{
	UGameplayStatics::OpenLevel(this, FName("RoguelikeShopMap"));
}
