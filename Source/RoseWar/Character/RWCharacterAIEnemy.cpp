// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RWCharacterAIEnemy.h"
#include "Animation/RWAnimInstance.h"
#include "Data/RWGameSingleton.h"
#include "Component/RWStatComponent.h"

FOnWarinessCommand ARWCharacterAIEnemy::OnEnemyWarinessCommand;
FOnAttackCommand ARWCharacterAIEnemy::OnEnemyAttackCommand;
FOnRetreatCommand ARWCharacterAIEnemy::OnEnemyRetreatCommand;
FOnRestCommand ARWCharacterAIEnemy::OnEnemyRestCommand;

ARWCharacterAIEnemy::ARWCharacterAIEnemy()
{
	HeadMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Head"));
	HeadMeshComp->SetupAttachment(GetMesh());
	HeadMeshComp->SetLeaderPoseComponent(GetMesh());

	HairMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hair"));
	HairMeshComp->SetupAttachment(GetMesh());
	HairMeshComp->SetLeaderPoseComponent(GetMesh());

	EyeMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Eye"));
	EyeMeshComp->SetupAttachment(GetMesh());
	EyeMeshComp->SetLeaderPoseComponent(GetMesh());

	HandMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hand"));
	HandMeshComp->SetupAttachment(GetMesh());
	HandMeshComp->SetLeaderPoseComponent(GetMesh());

	LegMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Leg"));
	LegMeshComp->SetupAttachment(GetMesh());
	LegMeshComp->SetLeaderPoseComponent(GetMesh());

	FeetMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Feet"));
	FeetMeshComp->SetupAttachment(GetMesh());
	FeetMeshComp->SetLeaderPoseComponent(GetMesh());

	LeftWeaponMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Weapon"));
	LeftWeaponMeshComp->SetupAttachment(GetMesh(), TEXT("hand_lSocket"));

	RightWeaponMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Weapon"));
	RightWeaponMeshComp->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));

	TeamId = FGenericTeamId(1);
}

FGenericTeamId ARWCharacterAIEnemy::GetGenericTeamId() const
{
	return TeamId;
}

void ARWCharacterAIEnemy::ReadyForBattle()
{
	URWAnimInstance* RWAnim = Cast<URWAnimInstance>(GetMesh()->GetAnimInstance());
	if (RWAnim)
	{
		RWAnim->bIsWariness = true;
	}
}

void ARWCharacterAIEnemy::ReadyForRest()
{
	URWAnimInstance* RWAnim = Cast<URWAnimInstance>(GetMesh()->GetAnimInstance());
	if (RWAnim)
	{
		RWAnim->bIsWariness = false;
	}
}

float ARWCharacterAIEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	CheckDeath() ? URWGameSingleton::Get().SubAIEnemyHealth(Damage + StatComp->GetCurrentHp()) : URWGameSingleton::Get().SubAIEnemyHealth(Damage);

	return 0.0f;
}

float ARWCharacterAIEnemy::GetCurrentHp() const
{
	UE_LOG(LogTemp, Display, TEXT("%s 의 현재 체력 : %f"), *GetActorNameOrLabel(), StatComp->GetCurrentHp());
	return StatComp->GetCurrentHp();
}

float ARWCharacterAIEnemy::GetMaxHp() const
{
	return StatComp->GetTotalStat().MaxHp;
}

void ARWCharacterAIEnemy::SetDead()
{
	Super::SetDead();
	URWGameSingleton::Get().ReleaseEnemy(this);
}

