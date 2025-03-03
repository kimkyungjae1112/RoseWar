// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DeathMatchGameWidget.generated.h"

class UTextBlock;

UCLASS()
class ROSEWAR_API UDeathMatchGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UDeathMatchGameWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	void ChangeRedScore(const FString& InScore);
	void ChangeBlueScore(const FString& InScore);
	void ChangeTimeLimit(const FString& InTime);

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTextBlock> ScoreRed;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTextBlock> ScoreBlue;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTextBlock> TimeLimitNum;
};
