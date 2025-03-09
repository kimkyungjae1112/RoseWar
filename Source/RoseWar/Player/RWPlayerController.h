// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RWPlayerController.generated.h"

class UHUDWidget;

UCLASS()
class ROSEWAR_API ARWPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ARWPlayerController();

	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

	void DisplayCommandWidget();
	void HiddenCommandWidget();
	void DisplayInteractWidget();
	void HiddenInteractWidget();
	bool IsInViewportInteractWidget();

	/* Roguelike Game */
	void NextStage();

protected:
	virtual void BeginPlay() override;

private:
	void ChangeInputModeToUIAndGame();
	void ChangeInputModeToGameOnly();

private:
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<UHUDWidget> HUDWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UHUDWidget> HUDWidget;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<UUserWidget> InteractWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UUserWidget> InteractWidget;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<UUserWidget> WinScreenWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<UUserWidget> LoseScreenWidgetClass;

	float RestartDelay = 5.f;
};
