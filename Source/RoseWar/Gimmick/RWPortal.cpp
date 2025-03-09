// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/RWPortal.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ARWPortal::ARWPortal()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComp;
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ARWPortal::BeginOverlap);
	BoxComp->SetCollisionProfileName(TEXT("Portal"));
}

void ARWPortal::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::OpenLevel(this, FName("RoguelikeBattleMap"));
}
