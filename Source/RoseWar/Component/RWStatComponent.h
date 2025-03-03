// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/RWCharacterStat.h"
#include "RWStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZero)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChanged, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROSEWAR_API URWStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URWStatComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FOnHpZero OnHpZero;
	FOnHpChanged OnHpChanged;

	void SetStat(const FName& InName);
	FORCEINLINE void SetModifierStat(const FRWCharacterStat& InModifierStat) { ModifierStat = InModifierStat; }
	FORCEINLINE float GetCurrentHp() const { return CurrentHp; }
	FORCEINLINE FRWCharacterStat GetTotalStat() const { return BaseStat + ModifierStat; }

	float ApplyDamage(float InDamage);

protected:
	void SetHp(float NewHp);
	
	UPROPERTY(Transient, VisibleInstanceOnly)
	float CurrentHp;

	UPROPERTY(Transient, VisibleInstanceOnly)
	FName CurrentName;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = "true"))
	FRWCharacterStat BaseStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = "true"))
	FRWCharacterStat ModifierStat;
};
