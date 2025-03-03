// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameSettingWidget.h"
#include "Components/EditableText.h"
#include "Components/Button.h"

UGameSettingWidget::UGameSettingWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UGameSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	EnemyCommandText = Cast<UEditableText>(GetWidgetFromName(TEXT("EnemyCommandText")));
	

	ConfirmButton = Cast<UButton>(GetWidgetFromName(TEXT("ConfirmButton")));
	ConfirmButton->OnClicked.AddDynamic(this, &UGameSettingWidget::EnemyCommandNumConfirm);
}

void UGameSettingWidget::EnemyCommandNumConfirm()
{
	if (EnemyCommandText)
	{
		int32 EnemyCommandNum = FCString::Atoi(*EnemyCommandText->GetText().ToString());
		if (EnemyCommandNum > 0 && EnemyCommandNum <= 4)
		{
			// 레벨에 EnemyCommandNum 숫자만큼 배치
			UE_LOG(LogTemp, Display, TEXT("Spawn EnemyCommand : %d"), EnemyCommandNum);
			OnCompleteSettings.ExecuteIfBound();
		}
	}
}

//ConfirmButton
