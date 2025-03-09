// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/RWCharacterStat.h"
#include "Data/RWAnimMontageData.h"
#include "Data/RWRoguelikeGameData.h"
#include "RWGameSingleton.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogRWGameSingleton, Error, All)
class ARWCharacterAIEnemy;

UCLASS()
class ROSEWAR_API URWGameSingleton : public UObject
{
	GENERATED_BODY()
	
public:
	URWGameSingleton();
	static URWGameSingleton& Get();


public:
	/* Character Stat Data */
	FORCEINLINE FRWCharacterStat GetCharacterStat(const FName& ClassName) const { return CharacterStatTable[ClassName]; }
	
	/* Character Montage Data */
	FORCEINLINE FRWAnimMontageData GetAnimMontage(const FName& ClassName) const { return AnimMontageTable[ClassName]; }

	/* AI Data */
	FORCEINLINE void InitializeHealth() { TotalAIEnemyHealth = CurrentAIEnemyHealth = 0.f; }
	FORCEINLINE float GetTotalMaxAIEnemyHealth() const { return TotalAIEnemyHealth; }
	FORCEINLINE float GetTotalCurrentAIEnemyHealth() const { return CurrentAIEnemyHealth; }
	void RegisterEnemy(ARWCharacterAIEnemy* AIEnemy);
	void ReleaseEnemy(ARWCharacterAIEnemy* AIEnemy);
	void SubAIEnemyHealth(float Health);

	/* Roguelike Game Data */
	FORCEINLINE FRWRoguelikeGameData GetRoguelikeGameData(int32 InStageLevel) const { return RoguelikeGameTable.IsValidIndex(InStageLevel) ? RoguelikeGameTable[InStageLevel] : FRWRoguelikeGameData(); }
	
	UPROPERTY()
	int32 StageMaxLevel;

private:
	/* Character Stat Data */
	UPROPERTY(VisibleAnywhere, Category = "Stat")
	TMap<FName, FRWCharacterStat> CharacterStatTable;

	/* Character Montage Data */
	UPROPERTY(VisibleAnywhere, Category = "Animation")
	TMap<FName, FRWAnimMontageData> AnimMontageTable;

	/* AI Data */
	UPROPERTY(VisibleAnywhere, Category = "Enemys")
	TArray<ARWCharacterAIEnemy*> AIEnemys;

	float TotalAIEnemyHealth = 0.f;
	float CurrentAIEnemyHealth = 0.f;

	/* Roguelike Game Data */
	TArray<FRWRoguelikeGameData> RoguelikeGameTable;
};
