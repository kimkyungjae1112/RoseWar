// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CommandWindowWidget.h"
#include "Components/Button.h"
#include "Character/RWCharacterBase.h"
#include "RoseWar.h"

UCommandWindowWidget::UCommandWindowWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCommandWindowWidget::NativeConstruct()
{
    Super::NativeConstruct();

    WarinessButton = Cast<UButton>(GetWidgetFromName(TEXT("WarinessButton")));
    AttackButton = Cast<UButton>(GetWidgetFromName(TEXT("AttackButton")));
    RetreatButton = Cast<UButton>(GetWidgetFromName(TEXT("RetreatButton")));
    RestButton = Cast<UButton>(GetWidgetFromName(TEXT("RestButton")));

    ensure(AttackButton);
    ensure(RetreatButton);
    ensure(RestButton);

    WarinessButton->OnClicked.AddDynamic(this, &UCommandWindowWidget::RunWarinessCommand);
    AttackButton->OnClicked.AddDynamic(this, &UCommandWindowWidget::RunAttackCommand);
    RetreatButton->OnClicked.AddDynamic(this, &UCommandWindowWidget::RunRetreatCommand);
    RestButton->OnClicked.AddDynamic(this, &UCommandWindowWidget::RunRestCommand);
}

void UCommandWindowWidget::RunWarinessCommand()
{
    RW_LOG(LogRoseWar, Display, TEXT("Wariness Button Click"));
    ARWCharacterBase::OnWarinessCommand.Broadcast();
}

void UCommandWindowWidget::RunAttackCommand()
{
    ARWCharacterBase::OnAttackCommand.Broadcast();
}

void UCommandWindowWidget::RunRetreatCommand()
{
    ARWCharacterBase::OnRetreatCommand.Broadcast();
}

void UCommandWindowWidget::RunRestCommand()
{
    ARWCharacterBase::OnRestCommand.Broadcast();
}
