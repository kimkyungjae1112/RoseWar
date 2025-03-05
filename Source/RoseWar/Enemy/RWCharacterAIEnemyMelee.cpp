// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/RWCharacterAIEnemyMelee.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Components/CapsuleComponent.h"
#include "Component/RWAIBehaviorComponent.h"
#include "AI/Controller/AIControllerEnemyMelee.h"

ARWCharacterAIEnemyMelee::ARWCharacterAIEnemyMelee()
{
	ClassName = TEXT("DualSword");

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/MRPGT/SkeletalMeshes/Humans/PlateArmour_C/SK_Plate_Torso_C_3_Black.SK_Plate_Torso_C_3_Black'"));
	if (BodyMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(BodyMeshRef.Object);
	}
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));	
	
	BehaviorComp = CreateDefaultSubobject<URWAIBehaviorComponent>(TEXT("Behavior Component"));
	BehaviorComp->OnCompAttackFinished.BindUObject(this, &ARWCharacterAIEnemyMelee::EndAttack);

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

void ARWCharacterAIEnemyMelee::AttackByAI()
{
	Super::AttackByAI();

	BeginAttack();
}

USkeletalMeshComponent* ARWCharacterAIEnemyMelee::GetSwordBone()
{
	return RightWeaponMeshComp;
}

void ARWCharacterAIEnemyMelee::ReadyForBattle()
{
	BehaviorComp->Wariness();
	LeftWeaponMeshComp->SetSkeletalMesh(WeaponMesh);
	RightWeaponMeshComp->SetSkeletalMesh(WeaponMesh);
	
	LeftWeaponSocketComp->SetSkeletalMesh(nullptr);
	RightWeaponSocketComp->SetSkeletalMesh(nullptr);
	//임시 -> Notify 로 옮길것
}

void ARWCharacterAIEnemyMelee::ReadyForRest()
{
	BehaviorComp->UnWariness();
	LeftWeaponMeshComp->SetSkeletalMesh(nullptr);
	RightWeaponMeshComp->SetSkeletalMesh(nullptr);

	LeftWeaponSocketComp->SetSkeletalMesh(WeaponMesh);
	RightWeaponSocketComp->SetSkeletalMesh(WeaponMesh);
	//임시 -> Notify 로 옮길것
}

float ARWCharacterAIEnemyMelee::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float SuperResult = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	RunParticle();

	return 0.0f;
}

void ARWCharacterAIEnemyMelee::BeginPlay()
{
	Super::BeginPlay();

}

void ARWCharacterAIEnemyMelee::SetDead()
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

void ARWCharacterAIEnemyMelee::BeginAttack()
{
	BehaviorComp->Attack();
}

void ARWCharacterAIEnemyMelee::EndAttack()
{
	OnAttackFinished.ExecuteIfBound();
}

AAIControllerEnemyMelee* ARWCharacterAIEnemyMelee::GetMyController()
{
	return CastChecked<AAIControllerEnemyMelee>(GetController());
}
