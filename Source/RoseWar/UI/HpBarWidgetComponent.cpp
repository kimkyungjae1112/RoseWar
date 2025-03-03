// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HpBarWidgetComponent.h"
#include "UI/HpBarBaseWidget.h"

void UHpBarWidgetComponent::InitWidget()
{
	Super::InitWidget();

	UHpBarBaseWidget* HpBarWidget = Cast<UHpBarBaseWidget>(GetWidget());
	if (HpBarWidget)
	{
		HpBarWidget->SetOwningActor(GetOwner());
	}
}
