
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "RWRoguelikeGameData.generated.h"

USTRUCT(BlueprintType)
struct FRWRoguelikeGameData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FRWRoguelikeGameData() : Money(0.f), EnemyNum(0) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameData")
	float Money;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 EnemyNum;
};