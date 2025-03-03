// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RWDominationGameMode.h"
#include "GameFramework/PlayerController.h"

ARWDominationGameMode::ARWDominationGameMode()
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

void ARWDominationGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
}

void ARWDominationGameMode::EndGame(bool bIsPlayerWinner)
{
}
