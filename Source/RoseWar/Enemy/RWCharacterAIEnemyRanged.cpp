// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/RWCharacterAIEnemyRanged.h"
#include "Components/CapsuleComponent.h"
#include "Component/RWAIBehaviorComponent.h"
#include "AI/Controller/AIControllerEnemyRanged.h"
#include "Weapon/RWArrow.h"

ARWCharacterAIEnemyRanged::ARWCharacterAIEnemyRanged()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/MRPGT/SkeletalMeshes/Humans/PlateArmour_C/SK_Plate_Torso_C_3.SK_Plate_Torso_C_3'"));
	if (BodyMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(BodyMeshRef.Object);
	}
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Friendly"));

	static ConstructorHelpers::FClassFinder<ARWArrow> ArrowClassRef(TEXT("/Game/Blueprints/Weapon/BP_RWArrow.BP_RWArrow_C"));
	if (ArrowClassRef.Class)
	{
		ArrowClass = ArrowClassRef.Class;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ArrowMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/MRPGT/StaticMeshes/Weapons/SM_Arrow_Simple_A.SM_Arrow_Simple_A'"));
	if (ArrowMeshRef.Object)
	{
		ArrowMesh = ArrowMeshRef.Object;
	}

	QuiverComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Quiver Component"));
	QuiverComp->SetupAttachment(GetMesh(), TEXT("quiverSocket"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> QuiverMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/MRPGT/SkeletalMeshes/Humans/Quivers/SK_Quiver_With_Arrows_A.SK_Quiver_With_Arrows_A'"));
	if (QuiverMeshRef.Object)
	{
		QuiverComp->SetSkeletalMesh(QuiverMeshRef.Object);
	}

	ArrowMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow Component"));
	ArrowMeshComp->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));

	BehaviorComp = CreateDefaultSubobject<URWAIBehaviorComponent>(TEXT("Behavior Component"));
	BehaviorComp->OnCompAttackFinished.BindUObject(this, &ARWCharacterAIEnemyRanged::EndAttack);
}

void ARWCharacterAIEnemyRanged::AttackByAI()
{
	Super::AttackByAI();

	BeginAttack();
}

float ARWCharacterAIEnemyRanged::GetAttackRange()
{
	return 1500.0f;
}

void ARWCharacterAIEnemyRanged::CreateArrow()
{
	ArrowMeshComp->SetStaticMesh(ArrowMesh);
}

void ARWCharacterAIEnemyRanged::ReleaseArrow()
{
	ArrowMeshComp->SetStaticMesh(nullptr);
	ARWArrow* Arrow = GetWorld()->SpawnActor<ARWArrow>(
		ArrowClass,
		GetMesh()->GetSocketLocation(TEXT("hand_lSocket")) + FVector(50.f, 0.f, 0.f),
		GetMesh()->GetSocketRotation(TEXT("hand_lSocket"))
	);
	Arrow->SetOwner(this);
	Arrow->FireArrow(GetActorForwardVector());
}

void ARWCharacterAIEnemyRanged::ReadyForBattle()
{
	BehaviorComp->Wariness();
}

void ARWCharacterAIEnemyRanged::ReadyForRest()
{
	BehaviorComp->UnWariness();
}

float ARWCharacterAIEnemyRanged::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float SuperResult = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	RunParticle();

	return 0.0f;
}

void ARWCharacterAIEnemyRanged::BeginPlay()
{
	Super::BeginPlay();

}

void ARWCharacterAIEnemyRanged::SetDead()
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

void ARWCharacterAIEnemyRanged::BeginAttack()
{
	BehaviorComp->Attack();
}

void ARWCharacterAIEnemyRanged::EndAttack()
{
	OnAttackFinished.ExecuteIfBound();
}

AAIControllerEnemyRanged* ARWCharacterAIEnemyRanged::GetMyController()
{
	return CastChecked<AAIControllerEnemyRanged>(GetController());
}
