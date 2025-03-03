// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameSettingWidget.generated.h"

class UEditableText;
class UButton;

DECLARE_DELEGATE(FOnCompleteSettings)

UCLASS()
class ROSEWAR_API UGameSettingWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UGameSettingWidget(const FObjectInitializer& ObjectInitializer);

	FOnCompleteSettings OnCompleteSettings;

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void EnemyCommandNumConfirm();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UEditableText> EnemyCommandText;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UButton> ConfirmButton;
};
