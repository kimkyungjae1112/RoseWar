// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "UI/GameSettingWidget.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SurvivalButton = Cast<UButton>(GetWidgetFromName(TEXT("SurvivalButton")));
	DeathMatchButton = Cast<UButton>(GetWidgetFromName(TEXT("DeathMatchButton")));
	DominationButton = Cast<UButton>(GetWidgetFromName(TEXT("DominationButton")));
	QuickButton = Cast<UButton>(GetWidgetFromName(TEXT("QuickButton")));
	GameSettingWidget = Cast<UGameSettingWidget>(GetWidgetFromName(TEXT("WBP_GameSetting")));

	ensure(SurvivalButton);
	ensure(DeathMatchButton);
	ensure(DominationButton);
	ensure(QuickButton);
	ensure(GameSettingWidget);

	GameSettingWidget->SetVisibility(ESlateVisibility::Hidden);
	GameSettingWidget->OnCompleteSettings.BindUObject(this, &UMainMenuWidget::OpenMap);

	SurvivalButton->OnClicked.AddDynamic(this, &UMainMenuWidget::SurvivalButtonClick);
	DeathMatchButton->OnClicked.AddDynamic(this, &UMainMenuWidget::DeathMatchButtonClick);
	DominationButton->OnClicked.AddDynamic(this, &UMainMenuWidget::DominationButtonClick);
	QuickButton->OnClicked.AddDynamic(this, &UMainMenuWidget::QuickButtonClick);
}

void UMainMenuWidget::SurvivalButtonClick()
{
	GameSettingWidget->SetVisibility(ESlateVisibility::Visible);
	GameModeIndex = 1;
}

void UMainMenuWidget::DeathMatchButtonClick()
{
	GameSettingWidget->SetVisibility(ESlateVisibility::Visible);
	GameModeIndex = 2;
}

void UMainMenuWidget::DominationButtonClick()
{
	GameSettingWidget->SetVisibility(ESlateVisibility::Visible);
	GameModeIndex = 3;
}

void UMainMenuWidget::QuickButtonClick()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UMainMenuWidget::OpenMap()
{
	switch (GameModeIndex)
	{
	case 1:
		OpenSurvivalMap();
		GameModeIndex = 0;
		return;
	case 2:
		OpenDeathMatchMap();
		GameModeIndex = 0;
		return;
	case 3:
		OpenDominationMap();
		GameModeIndex = 0;
		return;
	default:
		return;
	}
}

void UMainMenuWidget::OpenSurvivalMap()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("SurvivalMap"));
}

void UMainMenuWidget::OpenDeathMatchMap()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("DeathMatchMap"));
}

void UMainMenuWidget::OpenDominationMap()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("DominationMap"));
}



