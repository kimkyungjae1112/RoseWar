// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RWPlayerController.h"
#include "UI/HUDWidget.h"
#include "UI/CommandWindowWidget.h"

ARWPlayerController::ARWPlayerController()
{
	static ConstructorHelpers::FClassFinder<UHUDWidget> HUDWidgetClassRef(TEXT("/Game/UI/WBP_HUD.WBP_HUD_C"));
	if (HUDWidgetClassRef.Succeeded())
	{
		HUDWidgetClass = HUDWidgetClassRef.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> InteractWidgetClassRef(TEXT("/Game/UI/WBP_Interact.WBP_Interact_C"));
	if (InteractWidgetClassRef.Succeeded())
	{
		InteractWidgetClass = InteractWidgetClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> WinScreenWidgetClassRef(TEXT("/Game/UI/WBP_WinScreen.WBP_WinScreen_C"));
	if (WinScreenWidgetClassRef.Succeeded())
	{
		WinScreenWidgetClass = WinScreenWidgetClassRef.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> LoseScreenWidgetClassRef(TEXT("/Game/UI/WBP_LoseScreen.WBP_LoseScreen_C"));
	if (LoseScreenWidgetClassRef.Succeeded())
	{
		LoseScreenWidgetClass = LoseScreenWidgetClassRef.Class;
	}
}

void ARWPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	
	if (HUDWidget->IsInViewport())
	{
		HUDWidget->RemoveFromViewport();
	}

	if (bIsWinner)
	{
		UUserWidget* WinScreenWidget = CreateWidget(this, WinScreenWidgetClass);
		if (WinScreenWidget != nullptr)
		{
			WinScreenWidget->AddToViewport();
		}
	}
	else
	{
		UUserWidget* LoseScreenWidget = CreateWidget(this, LoseScreenWidgetClass);
		if (LoseScreenWidget != nullptr)
		{
			LoseScreenWidget->AddToViewport();
		}
	}

	FTimerHandle RestartTimer;
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

void ARWPlayerController::DisplayCommandWidget()
{
	HUDWidget->DisplayCommandWidget();

	ChangeInputModeToUIAndGame();
}

void ARWPlayerController::HiddenCommandWidget()
{
	HUDWidget->HiddenCommandWidget();

	ChangeInputModeToGameOnly();
}

void ARWPlayerController::DisplayInteractWidget()
{
	if (InteractWidget && !InteractWidget->IsInViewport())
	{
		InteractWidget->AddToViewport();
	}
}

void ARWPlayerController::HiddenInteractWidget()
{
	if (InteractWidget && InteractWidget->IsInViewport())
	{
		InteractWidget->RemoveFromViewport();
	}
}

bool ARWPlayerController::IsInViewportInteractWidget()
{
	if (InteractWidget == nullptr) return false;
	return InteractWidget->IsInViewport();
}

void ARWPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameMode;
	SetInputMode(GameMode);

	HUDWidget = CreateWidget<UHUDWidget>(this, HUDWidgetClass);
	if (HUDWidget)
	{
		HUDWidget->AddToViewport();
	}

	InteractWidget = CreateWidget(this, InteractWidgetClass);
	ensure(InteractWidget);
}

void ARWPlayerController::ChangeInputModeToUIAndGame()
{
	bShowMouseCursor = true;

	FInputModeGameAndUI GameMode;
	SetInputMode(GameMode);
}

void ARWPlayerController::ChangeInputModeToGameOnly()
{
	bShowMouseCursor = false;

	FInputModeGameOnly GameMode;
	SetInputMode(GameMode);
}
