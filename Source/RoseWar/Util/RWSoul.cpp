// Fill out your copyright notice in the Description page of Project Settings.


#include "Util/RWSoul.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ARWSoul::ARWSoul()
{
	RootComp= CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootComp;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComp);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);
}

void ARWSoul::BeginPlay()
{
	Super::BeginPlay();
	
}


