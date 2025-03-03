// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatusWidget.generated.h"

class UProgressBar;

UCLASS()
class ROSEWAR_API UStatusWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UStatusWidget(const FObjectInitializer& ObjectInitializer);
	
	void UpdateHpBar(float NewHp);
	void SetMaxHp(float InMaxHp);

protected:
	virtual void NativeConstruct() override;


private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProgressBar> HpBar;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProgressBar> CommandBar;

	float MaxHp;
};
