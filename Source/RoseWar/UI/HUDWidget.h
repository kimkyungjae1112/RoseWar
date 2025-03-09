// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UStatusWidget;
class UCommandWindowWidget;
class UTextBlock;

UCLASS()
class ROSEWAR_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UHUDWidget(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE bool GetIsOnCommandWidget() const { return bIsOnCommandWidget; }

/* Status Widget */
public:
	void UpdateHpBar(float NewHp);
	void SetMaxHp(float InMaxHp);

/* Command Widget */
public:
	void DisplayCommandWidget();
	void HiddenCommandWidget();

/* GameData */
public:
	void SetMoney(float InMoney);

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Status")
	TObjectPtr<UStatusWidget> StatusWidget;

	UPROPERTY(VisibleAnywhere, Category = "CommandWindow")
	TObjectPtr<UCommandWindowWidget> CommandWidget;

	UPROPERTY(VisibleAnywhere, Category = "Money")
	TObjectPtr<UTextBlock> MoneyWidget;

private:
	bool bIsOnCommandWidget = false;
};
