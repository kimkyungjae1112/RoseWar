// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RWCharacterAIFriendly.h"
#include "Animation/RWAnimInstance.h"

ARWCharacterAIFriendly::ARWCharacterAIFriendly() 
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

	TeamId = FGenericTeamId(0);
}

FGenericTeamId ARWCharacterAIFriendly::GetGenericTeamId() const
{
	return TeamId;
}

void ARWCharacterAIFriendly::ReadyForBattle()
{
	URWAnimInstance* RWAnim = Cast<URWAnimInstance>(GetMesh()->GetAnimInstance());
	if (RWAnim)
	{
		RWAnim->bIsWariness = true;
	}
}

void ARWCharacterAIFriendly::ReadyForRest()
{
	URWAnimInstance* RWAnim = Cast<URWAnimInstance>(GetMesh()->GetAnimInstance());
	if (RWAnim)
	{
		RWAnim->bIsWariness = false;
	}
}

void ARWCharacterAIFriendly::AttackByAI()
{
	Super::AttackByAI();

}
