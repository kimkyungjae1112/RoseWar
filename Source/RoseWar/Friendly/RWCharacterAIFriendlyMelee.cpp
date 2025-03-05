// Fill out your copyright notice in the Description page of Project Settings.


#include "Friendly/RWCharacterAIFriendlyMelee.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Components/CapsuleComponent.h"
#include "Component/RWAIBehaviorComponent.h"
#include "AI/Controller/AIControllerFriendlyMelee.h"

ARWCharacterAIFriendlyMelee::ARWCharacterAIFriendlyMelee()
{
	ClassName = TEXT("DualSword");

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/MRPGT/SkeletalMeshes/Humans/PlateArmour_C/SK_Plate_Torso_C_3.SK_Plate_Torso_C_3'"));
	if (BodyMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(BodyMeshRef.Object);
	}
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Friendly"));

	BehaviorComp = CreateDefaultSubobject<URWAIBehaviorComponent>(TEXT("Behavior Component"));
	BehaviorComp->OnCompAttackFinished.BindUObject(this, &ARWCharacterAIFriendlyMelee::EndAttack);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/SKnight_modular/Skeleton_Knight_01/mesh/weapon/SK_weapon_01.SK_weapon_01'"));
	if (WeaponMeshRef.Object)
	{
		WeaponMesh = WeaponMeshRef.Object;
	}

	LeftWeaponSocketComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftWeaponSocketComponent"));
	LeftWeaponSocketComp->SetupAttachment(GetMesh());
	LeftWeaponSocketComp->SetLeaderPoseComponent(GetMesh());
	LeftWeaponSocketComp->SetSkeletalMesh(WeaponMesh);

	RightWeaponSocketComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightWeaponSocketComponent"));
	RightWeaponSocketComp->SetupAttachment(GetMesh());
	RightWeaponSocketComp->SetLeaderPoseComponent(GetMesh());
	RightWeaponSocketComp->SetSkeletalMesh(WeaponMesh);
}

void ARWCharacterAIFriendlyMelee::AttackByAI()
{
	Super::AttackByAI();

	BeginAttack();
}

USkeletalMeshComponent* ARWCharacterAIFriendlyMelee::GetSwordBone()
{
	return RightWeaponMeshComp;
}

void ARWCharacterAIFriendlyMelee::ReadyForBattle()
{
	BehaviorComp->Wariness();
	LeftWeaponMeshComp->SetSkeletalMesh(WeaponMesh);
	RightWeaponMeshComp->SetSkeletalMesh(WeaponMesh);

	LeftWeaponSocketComp->SetSkeletalMesh(nullptr);
	RightWeaponSocketComp->SetSkeletalMesh(nullptr);
}

void ARWCharacterAIFriendlyMelee::ReadyForRest()
{
	BehaviorComp->UnWariness();
	LeftWeaponMeshComp->SetSkeletalMesh(nullptr);
	RightWeaponMeshComp->SetSkeletalMesh(nullptr);

	LeftWeaponSocketComp->SetSkeletalMesh(WeaponMesh);
	RightWeaponSocketComp->SetSkeletalMesh(WeaponMesh);
}

float ARWCharacterAIFriendlyMelee::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float SuperResult = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	RunParticle();

	return 0.0f;
}

void ARWCharacterAIFriendlyMelee::BeginPlay()
{
	Super::BeginPlay();

}

void ARWCharacterAIFriendlyMelee::SetDead()
{
	Super::SetDead();

	BehaviorComp->Dead();
	GetMyController()->StopAI();
	SetActorEnableCollision(false);

	FTimerHandle DestroyTimer;
	GetWorld()->GetTimerManager().SetTimer(DestroyTimer, [&]()
		{
			Destroy();
		}, 5.f, false);

	DetachFromControllerPendingDestroy();
}

void ARWCharacterAIFriendlyMelee::BeginAttack()
{
	BehaviorComp->Attack();
}

void ARWCharacterAIFriendlyMelee::EndAttack()
{
	OnAttackFinished.ExecuteIfBound();
}

AAIControllerFriendlyMelee* ARWCharacterAIFriendlyMelee::GetMyController()
{
	return CastChecked<AAIControllerFriendlyMelee>(GetController());
}
