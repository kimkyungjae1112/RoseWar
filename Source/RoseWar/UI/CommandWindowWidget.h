// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CommandWindowWidget.generated.h"

class UButton;

UCLASS()
class ROSEWAR_API UCommandWindowWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UCommandWindowWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void RunWarinessCommand();

	UFUNCTION()
	void RunAttackCommand();

	UFUNCTION()
	void RunRetreatCommand();

	UFUNCTION()
	void RunRestCommand();

	UPROPERTY(VisibleAnywhere, Category = "Button")
	TObjectPtr<UButton> WarinessButton;

	UPROPERTY(VisibleAnywhere, Category = "Button")
	TObjectPtr<UButton> AttackButton;

	UPROPERTY(VisibleAnywhere, Category = "Button")
	TObjectPtr<UButton> RetreatButton;

	UPROPERTY(VisibleAnywhere, Category = "Button")
	TObjectPtr<UButton> RestButton;
};
