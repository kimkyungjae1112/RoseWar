// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;
class UGameSettingWidget;

UCLASS()
class ROSEWAR_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMainMenuWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SurvivalButtonClick();

	UFUNCTION()
	void DeathMatchButtonClick();

	UFUNCTION()
	void DominationButtonClick();

	UFUNCTION()
	void QuickButtonClick();

	void OpenMap();
	void OpenSurvivalMap();
	void OpenDeathMatchMap();
	void OpenDominationMap();

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UGameSettingWidget> GameSettingWidget;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UButton> SurvivalButton;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UButton> DeathMatchButton;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UButton> DominationButton;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UButton> QuickButton;

	int32 GameModeIndex = 0;
};
