// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/RWGameSingleton.h"
#include "Character/RWCharacterAIEnemy.h"
#include "RoseWar.h"

DEFINE_LOG_CATEGORY(LogRWGameSingleton)

URWGameSingleton::URWGameSingleton()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> StatDataTableRef(TEXT("/Script/Engine.DataTable'/Game/Data/RWCharacterStatTable.RWCharacterStatTable'"));
	if (StatDataTableRef.Succeeded())
	{
		const UDataTable* StatDataTable = StatDataTableRef.Object;
		check(StatDataTable->GetRowMap().Num() > 0);

		for (const auto& Elem : StatDataTable->GetRowMap())
		{
			const FName& RowName = Elem.Key;
			const FRWCharacterStat* StatPtr = reinterpret_cast<const FRWCharacterStat*>(Elem.Value);
			if (StatPtr)
			{
				CharacterStatTable.Add(RowName, *StatPtr);
			}
		}
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> AnimMontageDataTableRef(TEXT("/Script/Engine.DataTable'/Game/Data/RWAnimMontageDataTable.RWAnimMontageDataTable'"));
	if (AnimMontageDataTableRef.Succeeded())
	{
		const UDataTable* AnimMontageDataTable = AnimMontageDataTableRef.Object;
		check(AnimMontageDataTable->GetRowMap().Num() > 0);

		for (const auto& Elem : AnimMontageDataTable->GetRowMap())
		{
			const FName& RowName = Elem.Key;
			const FRWAnimMontageData* StatPtr = reinterpret_cast<const FRWAnimMontageData*>(Elem.Value);
			if (StatPtr)
			{
				AnimMontageTable.Add(RowName, *StatPtr);
			}
		}
	}
}

URWGameSingleton& URWGameSingleton::Get()
{
	URWGameSingleton* Singleton = CastChecked<URWGameSingleton>(GEngine->GameSingleton);
	if (Singleton)
	{
		return *Singleton;
	}

	UE_LOG(LogRWGameSingleton, Error, TEXT("Invaild Game Singleton"));
	return *NewObject<URWGameSingleton>();
}

void URWGameSingleton::RegisterEnemy(ARWCharacterAIEnemy* AIEnemy)
{
	AIEnemys.Add(AIEnemy);

	TotalAIEnemyHealth += AIEnemy->GetMaxHp();
	CurrentAIEnemyHealth = TotalAIEnemyHealth;

	RW_LOG(LogRoseWar, Display, TEXT("Enemys Total Health : %f"), TotalAIEnemyHealth);
}

void URWGameSingleton::ReleaseEnemy(ARWCharacterAIEnemy* AIEnemy)
{
	if (AIEnemy->CheckDeath())
	{
		TotalAIEnemyHealth -= AIEnemy->GetMaxHp();
		AIEnemys.Remove(AIEnemy);

		RW_LOG(LogRoseWar, Display, TEXT("Enemys Total Health After Release : %f"), TotalAIEnemyHealth);
	}
}

void URWGameSingleton::SubAIEnemyHealth(float Health)
{
	CurrentAIEnemyHealth -= Health;

	RW_LOG(LogRoseWar, Display, TEXT("Enemys 감소 체력 : %f"), CurrentAIEnemyHealth);
}
