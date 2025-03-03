// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HpBarWidget.h"
#include "Interface/HpBarInterface.h"
#include "Components/ProgressBar.h"

UHpBarWidget::UHpBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.f;
}

void UHpBarWidget::SetMaxHp(float InMaxHp)
{
	MaxHp = InMaxHp;
}

void UHpBarWidget::UpdateHpBar(float NewHp)
{
	HpBar->SetPercent(NewHp / MaxHp);
}

void UHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HpBar")));
	ensure(HpBar);

	IHpBarInterface* Interface = Cast<IHpBarInterface>(OwningActor);
	if (Interface)
	{
		Interface->SetupHpBarWidget(this);
	}
}
