// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/RWAIBehaviorComponent.h"
#include "Data/RWGameSingleton.h"
#include "Interface/ClassIdentifierInterface.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

URWAIBehaviorComponent::URWAIBehaviorComponent()
{
}

void URWAIBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<ACharacter>(GetOwner());
	check(Character);
	Anim = Character->GetMesh()->GetAnimInstance();
	check(Anim);

	IClassIdentifierInterface* CII = Cast<IClassIdentifierInterface>(GetOwner());
	if (CII)
	{
		AnimMontageData = URWGameSingleton::Get().GetAnimMontage(CII->SetupClassName());
	}
}

void URWAIBehaviorComponent::Attack()
{
	if (AnimMontageData.AttackMontage.IsPending())
	{
		AnimMontageData.AttackMontage.LoadSynchronous();
	}

	UAnimMontage* AttackMontage = AnimMontageData.AttackMontage.Get();
	Anim->Montage_Play(AttackMontage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &URWAIBehaviorComponent::EndAttack);
	Anim->Montage_SetEndDelegate(MontageEnd, AttackMontage);
}

void URWAIBehaviorComponent::Dead()
{
	if (AnimMontageData.DeadMontage.IsPending())
	{
		AnimMontageData.DeadMontage.LoadSynchronous();
	}

	Anim->Montage_Play(AnimMontageData.DeadMontage.Get());
}

void URWAIBehaviorComponent::Wariness()
{
	if (AnimMontageData.WarinessMontage.IsPending())
	{
		AnimMontageData.WarinessMontage.LoadSynchronous();
	}

	UAnimMontage* WarinessMontage = AnimMontageData.WarinessMontage.Get();
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	Anim->Montage_Play(WarinessMontage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &URWAIBehaviorComponent::EndWariness);
	Anim->Montage_SetEndDelegate(MontageEnd, WarinessMontage);
}

void URWAIBehaviorComponent::UnWariness()
{
	if (AnimMontageData.UnWarinessMontage.IsPending())
	{
		AnimMontageData.UnWarinessMontage.LoadSynchronous();
	}

	UAnimMontage* UnWarinessMontage = AnimMontageData.UnWarinessMontage.Get();
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	Anim->Montage_Play(UnWarinessMontage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &URWAIBehaviorComponent::EndUnWariness);
	Anim->Montage_SetEndDelegate(MontageEnd, UnWarinessMontage);
}

void URWAIBehaviorComponent::EndAttack(UAnimMontage* Target, bool IsProperlyEnded)
{
	OnCompAttackFinished.ExecuteIfBound();
}

void URWAIBehaviorComponent::EndWariness(UAnimMontage* Target, bool IsProperlyEnded)
{
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void URWAIBehaviorComponent::EndUnWariness(UAnimMontage* Target, bool IsProperlyEnded)
{
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}


