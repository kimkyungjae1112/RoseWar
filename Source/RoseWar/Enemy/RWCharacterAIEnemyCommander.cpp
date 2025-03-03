// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/RWCharacterAIEnemyCommander.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Components/CapsuleComponent.h"
#include "AI/Controller/AIControllerEnemyCommander.h"
#include "NiagaraComponent.h"
#include "Component/RWAIBehaviorComponent.h"
#include "RoseWar.h"

ARWCharacterAIEnemyCommander::ARWCharacterAIEnemyCommander()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/MRPGT/SkeletalMeshes/Humans/PlateArmour_C/SK_Plate_Torso_C_3_Black.SK_Plate_Torso_C_3_Black'"));
	if (BodyMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(BodyMeshRef.Object);
	}
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	
	Tags.Add(TEXT("Commander"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

	BehaviorComp = CreateDefaultSubobject<URWAIBehaviorComponent>(TEXT("Behavior Component"));
}

void ARWCharacterAIEnemyCommander::EnemyWarinessCommand()
{
	OnEnemyWarinessCommand.Broadcast();
}

void ARWCharacterAIEnemyCommander::EnemyAttackCommand()
{
	OnEnemyAttackCommand.Broadcast();
}

void ARWCharacterAIEnemyCommander::EnemyRetreatCommand()
{
	OnEnemyRetreatCommand.Broadcast();
}

void ARWCharacterAIEnemyCommander::EnemyRestCommand()
{
	OnEnemyRestCommand.Broadcast();
}

void ARWCharacterAIEnemyCommander::AttackByAI()
{
	Super::AttackByAI();

	BeginAttack();
}

USkeletalMeshComponent* ARWCharacterAIEnemyCommander::GetSwordBone()
{
	return RightWeaponMeshComp;
}

float ARWCharacterAIEnemyCommander::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float SuperResult = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	RunParticle();

	return 0.0f;
}

void ARWCharacterAIEnemyCommander::BeginPlay()
{
	Super::BeginPlay();

}

void ARWCharacterAIEnemyCommander::SetDead()
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

void ARWCharacterAIEnemyCommander::BeginAttack()
{
	BehaviorComp->Attack();
}

void ARWCharacterAIEnemyCommander::EndAttack()
{
	OnAttackFinished.ExecuteIfBound();
}

AAIControllerEnemyCommander* ARWCharacterAIEnemyCommander::GetMyController()
{
	return CastChecked<AAIControllerEnemyCommander>(GetController());
}



