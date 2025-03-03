// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RWCharacterBase.h"

FOnWarinessCommand ARWCharacterBase::OnWarinessCommand;
FOnAttackCommand ARWCharacterBase::OnAttackCommand;
FOnRetreatCommand ARWCharacterBase::OnRetreatCommand;
FOnRestCommand ARWCharacterBase::OnRestCommand;

//FCharacterIdleState FCharacterState::CharacterIdleState;
//FCharacterWalkState FCharacterState::CharacterWalkState;
//FCharacterRunState FCharacterState::CharacterRunState;
//FCharacterDetectEnemyState FCharacterState::CharacterDetectEnemyState;
//FCharacterAttackingState FCharacterState::CharacterAttackingState;

ARWCharacterBase::ARWCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

FGenericTeamId ARWCharacterBase::GetGenericTeamId() const
{
	return FGenericTeamId();
}

void ARWCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARWCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ARWCharacterBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float SuperResult = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	return 0.0f;
}

void ARWCharacterBase::Damaged(float DamageAmount, AActor* DamageCauser, const FName& DamageType)
{

}

//void FCharacterIdleState::HandleInput(ARWCharacterBase* Character)
//{
//	if (Character->GetMovingSpeed() > 3.f)
//	{
//		UE_LOG(LogTemp, Display, TEXT("Character State Idle -> Walk"));
//		Character->SetState(&FCharacterState::CharacterWalkState);
//	}
//}
//
//void FCharacterWalkState::HandleInput(ARWCharacterBase* Character)
//{
//	Character->Walk();
//
//	if (Character->GetMovingSpeed() > 400.f)
//	{
//		UE_LOG(LogTemp, Display, TEXT("Character State Walk -> Run"));
//		Character->SetState(&FCharacterState::CharacterRunState);
//	}
//	else if (Character->GetMovingSpeed() < 3.f)
//	{
//		UE_LOG(LogTemp, Display, TEXT("Character State Walk -> Idle"));
//		Character->SetState(&FCharacterState::CharacterIdleState);
//	}
//}
//
//void FCharacterRunState::HandleInput(ARWCharacterBase* Character)
//{
//	Character->Run();
//
//	if (Character->GetMovingSpeed() < 400.f)
//	{
//		UE_LOG(LogTemp, Display, TEXT("Character State Run -> Walk"));
//		Character->SetState(&FCharacterState::CharacterWalkState);
//	}
//}
