// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/RWArrow.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "RoseWar.h"
#include "Engine/DamageEvents.h"

ARWArrow::ARWArrow()
{
    PrimaryActorTick.bCanEverTick = true;

    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    CollisionComp->InitSphereRadius(2.0f);
    CollisionComp->SetCollisionProfileName(TEXT("Arrow"));
    CollisionComp->OnComponentHit.AddDynamic(this, &ARWArrow::ArrowHit);
    RootComponent = CollisionComp;

    ArrowMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMesh"));
    ArrowMeshComp->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ArrowMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/MRPGT/StaticMeshes/Weapons/SM_Arrow_Simple_A.SM_Arrow_Simple_A'"));
    if (ArrowMeshRef.Object)
    {
        ArrowMeshComp->SetStaticMesh(ArrowMeshRef.Object);
    }

    ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovementComp->UpdatedComponent = CollisionComp;
    ProjectileMovementComp->InitialSpeed = 900.f;
    ProjectileMovementComp->MaxSpeed = 900.f;
    ProjectileMovementComp->bAutoActivate = false;
    ProjectileMovementComp->bRotationFollowsVelocity = true;
    ProjectileMovementComp->bShouldBounce = false;
    ProjectileMovementComp->ProjectileGravityScale = 0.5f;
}

void ARWArrow::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARWArrow::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    DrawDebugPoint(GetWorld(), GetActorLocation(), 12, FColor::Red, false, 3.f);
}

void ARWArrow::FireArrow(const FVector& Dir)
{
    ProjectileMovementComp->Velocity = Dir * ProjectileMovementComp->InitialSpeed;
    ProjectileMovementComp->Activate();
}

void ARWArrow::ArrowHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor)
    {
        RW_LOG(LogRoseWar, Display, TEXT("OtherActor Name : %s"), *OtherActor->GetActorNameOrLabel());

        FDamageEvent DamageEvent;
        APawn* OwnerPawn = Cast<APawn>(GetOwner());
        if (OwnerPawn)
        {
            OtherActor->TakeDamage(100.f, DamageEvent, OwnerPawn->GetController(), OwnerPawn);
        }
    }

    CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    FTimerHandle DestroyTimer;
    GetWorld()->GetTimerManager().SetTimer(DestroyTimer, [&]()
    {
        Destroy();
    }, 5.f, false);
}



