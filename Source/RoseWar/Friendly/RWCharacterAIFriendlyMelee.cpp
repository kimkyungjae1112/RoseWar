// Fill out your copyright notice in the Description page of Project Settings.


#include "Friendly/RWCharacterAIFriendlyMelee.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Components/CapsuleComponent.h"
#include "Component/RWAIBehaviorComponent.h"
#include "AI/Controller/AIControllerFriendlyMelee.h"

ARWCharacterAIFriendlyMelee::ARWCharacterAIFriendlyMelee()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/MRPGT/SkeletalMeshes/Humans/PlateArmour_C/SK_Plate_Torso_C_3.SK_Plate_Torso_C_3'"));
	if (BodyMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(BodyMeshRef.Object);
	}
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Friendly"));

	BehaviorComp = CreateDefaultSubobject<URWAIBehaviorComponent>(TEXT("Behavior Component"));
	BehaviorComp->OnCompAttackFinished.BindUObject(this, &ARWCharacterAIFriendlyMelee::EndAttack);
}

void ARWCharacterAIFriendlyMelee::AttackByAI()
{
	Super::AttackByAI();

	BeginAttack();
}

float ARWCharacterAIFriendlyMelee::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float SuperResult = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	RunParticle();

	return 0.0f;
}

USkeletalMeshComponent* ARWCharacterAIFriendlyMelee::GetSwordBone()
{
	return RightWeaponMeshComp;
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
