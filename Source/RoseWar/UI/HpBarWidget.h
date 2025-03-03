// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HpBarBaseWidget.h"
#include "HpBarWidget.generated.h"

class UProgressBar;

UCLASS()
class ROSEWAR_API UHpBarWidget : public UHpBarBaseWidget
{
	GENERATED_BODY()
	
public:
	UHpBarWidget(const FObjectInitializer& ObjectInitializer);

	void SetMaxHp(float InMaxHp);
	void UpdateHpBar(float NewHp);

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProgressBar> HpBar;

	float MaxHp;
};
