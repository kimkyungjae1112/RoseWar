// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact/RWHorse.h"
#include "Animation/AnimInstance.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Player/RWPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

ARWHorse::ARWHorse()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetCollisionProfileName(TEXT("Horse"));
	RootComponent = BoxComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(RootComponent);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ARWHorse::OnBeginOverlap);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &ARWHorse::OnEndOverlap);

	BodyMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMeshComp"));
	BodyMeshComp->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/MRPGT/SkeletalMeshes/Horse/SK_Horse_A.SK_Horse_A'"));
	if (BodyMeshRef.Object)
	{
		BodyMeshComp->SetSkeletalMesh(BodyMeshRef.Object);
		BodyMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	}

	TackMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TackMesh"));
	TackMeshComp->SetupAttachment(BodyMeshComp, TEXT("HorseSeat"));
	TackMeshComp->SetMasterPoseComponent(BodyMeshComp);
	TackMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
}

void ARWHorse::BeginPlay()
{
	Super::BeginPlay();
	
	/*Anim = BodyMeshComp->GetAnimInstance();
	ensure(Anim);*/
}

void ARWHorse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARWHorse::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ARWHorse::HorsePossess(ARWPlayerController* PC)
{

}

void ARWHorse::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && this != OtherActor && OtherActor->ActorHasTag(TEXT("Commander")))
	{
		ARWPlayerController* PC = Cast<ARWPlayerController>(GetWorld()->GetFirstPlayerController());
		if (PC)
		{
			PC->DisplayInteractWidget();
		}
	}
}

void ARWHorse::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && this != OtherActor)
	{
		ARWPlayerController* PC = Cast<ARWPlayerController>(GetWorld()->GetFirstPlayerController());
		if (PC)
		{
			PC->HiddenInteractWidget();
		}
	}
}


