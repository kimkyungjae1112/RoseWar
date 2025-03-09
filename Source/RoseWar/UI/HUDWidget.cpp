// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDWidget.h"
#include "UI/StatusWidget.h"
#include "UI/CommandWindowWidget.h"
#include "Components/TextBlock.h"
#include "Interface/HUDInterface.h"

UHUDWidget::UHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UHUDWidget::UpdateHpBar(float NewHp)
{
	StatusWidget->UpdateHpBar(NewHp);
}

void UHUDWidget::SetMaxHp(float InMaxHp)
{
	StatusWidget->SetMaxHp(InMaxHp);
}

void UHUDWidget::DisplayCommandWidget()
{
	bIsOnCommandWidget = true;
	CommandWidget->SetVisibility(ESlateVisibility::Visible);
}

void UHUDWidget::HiddenCommandWidget()
{
	bIsOnCommandWidget = false;
	CommandWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UHUDWidget::SetMoney(float InMoney)
{
	FString Text = FString::Printf(TEXT("%0.2f"), InMoney);
	MoneyWidget->SetText(FText::FromString(Text));
}

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StatusWidget = Cast<UStatusWidget>(GetWidgetFromName(TEXT("WBP_Status")));
	CommandWidget = Cast<UCommandWindowWidget>(GetWidgetFromName(TEXT("WBP_CommandWindow")));
	MoneyWidget = Cast<UTextBlock>(GetWidgetFromName(TEXT("Money")));

	ensure(StatusWidget);
	ensure(CommandWidget);
	ensure(MoneyWidget);

	IHUDInterface* Interface = Cast<IHUDInterface>(GetOwningPlayerPawn());
	if (Interface)
	{
		Interface->SetHUDWidget(this);
	}

	HiddenCommandWidget();
}
