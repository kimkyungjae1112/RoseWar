// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "Interface/ClassIdentifierInterface.h"
#include "RWCharacterBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnWarinessCommand)
DECLARE_MULTICAST_DELEGATE(FOnAttackCommand)
DECLARE_MULTICAST_DELEGATE(FOnRetreatCommand)
DECLARE_MULTICAST_DELEGATE(FOnRestCommand)


// 상태 패턴을 도입하면,,,, 
// 우선 플레이어는 여러가지 무기를 쓸까? -> 기획 ;;; -> 내가 볼 땐 검 & 화살 두가지 종류만 하는게 좋아보임..
// 그럼 플레이어는 우선 병행 상태 머신으로 사용
// 그럼 상태에는 무엇 무엇이 있어야 하나
	// Idle -> Walk -> Run -> Crouch -> DetectEnemy -> Attaking -> Defence -> ??
// AI의 블랙보드에 있는 불리언 값을 모두 상태 머신으로 만들어야 하나?

//USTRUCT()
//struct FCharacterState
//{
//	GENERATED_BODY()
//
//public:
//	FCharacterState() = default;
//
//	static FCharacterIdleState CharacterIdleState;
//	static FCharacterWalkState CharacterWalkState;
//	static FCharacterRunState CharacterRunState;
//	static FCharacterDetectEnemyState CharacterDetectEnemyState;
//	static FCharacterAttackingState CharacterAttackingState;
//
//	virtual void HandleInput(ARWCharacterBase* Character) {}
//};
//
//USTRUCT()
//struct FCharacterIdleState : public FCharacterState
//{
//	GENERATED_BODY()
//
//public:
//	virtual void HandleInput(ARWCharacterBase* Character);
//};
//
//USTRUCT()
//struct FCharacterWalkState : public FCharacterState
//{
//	GENERATED_BODY()
//
//public:
//	virtual void HandleInput(ARWCharacterBase* Character);
//
//};
//
//USTRUCT()
//struct FCharacterRunState : public FCharacterState
//{
//	GENERATED_BODY()
//
//public:
//	virtual void HandleInput(ARWCharacterBase* Character);
//
//};
//
//USTRUCT()
//struct FCharacterDetectEnemyState : public FCharacterState
//{
//	GENERATED_BODY()
//
//};
//
//USTRUCT()
//struct FCharacterAttackingState : public FCharacterState
//{
//	GENERATED_BODY()
//
//};

UCLASS()
class ROSEWAR_API ARWCharacterBase : public ACharacter, public IGenericTeamAgentInterface, public IClassIdentifierInterface
{
	GENERATED_BODY()

public:
	ARWCharacterBase();

	/* IGenericTeamAgentInterface Implement */
	virtual FGenericTeamId GetGenericTeamId() const override;

	/* IClassIdentifierInterface Implement */
	virtual FName SetupClassName() override { return ClassName; }

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	static FOnWarinessCommand OnWarinessCommand;
	static FOnAttackCommand OnAttackCommand;
	static FOnRetreatCommand OnRetreatCommand;
	static FOnRestCommand OnRestCommand;

	/*virtual void SetState(FCharacterState* InState) {}
	virtual float GetMovingSpeed() { return float(); }
	virtual void Walk() {}
	virtual void Run() {}*/

protected:
	virtual void BeginPlay() override;

	FGenericTeamId TeamId;
	
	/* 블루프린트에서 해당 값을 조절한다. */
	UPROPERTY(EditDefaultsOnly, Category = "Class")
	FName ClassName;


public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Damaged(float DamageAmount, AActor* DamageCauser, const FName& DamageType);

};


