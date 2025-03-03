// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RWGameMode.h"
#include "UI/MainMenuWidget.h"

ARWGameMode::ARWGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Game/Blueprints/Util/BP_RWSoul.BP_RWSoul_C"));
	if (DefaultPawnClassRef.Succeeded())
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}
	static ConstructorHelpers::FClassFinder<UMainMenuWidget> MainMenuClassRef(TEXT("/Game/UI/WBP_MainMenu.WBP_MainMenu_C"));
	if (MainMenuClassRef.Succeeded())
	{
		MainMenuClass = MainMenuClassRef.Class;
	}
}

void ARWGameMode::BeginPlay()
{
	Super::BeginPlay();

	MainMenuPtr = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuClass);
	if (MainMenuPtr)
	{
		MainMenuPtr->AddToViewport();
	}
}
