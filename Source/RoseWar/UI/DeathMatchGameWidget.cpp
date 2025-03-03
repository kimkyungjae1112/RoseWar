// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DeathMatchGameWidget.h"
#include "Components/TextBlock.h"

UDeathMatchGameWidget::UDeathMatchGameWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UDeathMatchGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ScoreRed = Cast<UTextBlock>(GetWidgetFromName(TEXT("ScoreRed")));
	ScoreBlue = Cast<UTextBlock>(GetWidgetFromName(TEXT("ScoreBlue")));
	TimeLimitNum = Cast<UTextBlock>(GetWidgetFromName(TEXT("TimeLimitNum")));

	ensure(ScoreRed);
	ensure(ScoreBlue);
	ensure(TimeLimitNum);
}

void UDeathMatchGameWidget::ChangeRedScore(const FString& InScore)
{
	ScoreRed->SetText(FText::FromString(InScore));
}

void UDeathMatchGameWidget::ChangeBlueScore(const FString& InScore)
{
	ScoreBlue->SetText(FText::FromString(InScore));
}

void UDeathMatchGameWidget::ChangeTimeLimit(const FString& InTime)
{
	TimeLimitNum->SetText(FText::FromString(InTime));
}
