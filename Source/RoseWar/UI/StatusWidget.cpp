// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StatusWidget.h"
#include "Components/ProgressBar.h"

UStatusWidget::UStatusWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.f;
}

void UStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HpBar")));
	CommandBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_CommandBar")));

	ensure(HpBar);
	ensure(CommandBar);
}

void UStatusWidget::UpdateHpBar(float NewHp)
{
	HpBar->SetPercent(NewHp / MaxHp);
}

void UStatusWidget::SetMaxHp(float InMaxHp)
{
	MaxHp = InMaxHp;
}
