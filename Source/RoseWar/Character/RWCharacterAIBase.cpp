// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RWCharacterAIBase.h"
#include "UI/HpBarWidgetComponent.h"
#include "UI/HpBarWidget.h"
#include "Component/RWStatComponent.h"
#include "Game/RWInGameModeBase.h"
#include "NiagaraComponent.h"

ARWCharacterAIBase::ARWCharacterAIBase()
{
	StatComp = CreateDefaultSubobject<URWStatComponent>(TEXT("Stat Component"));
	StatComp->OnHpZero.AddUObject(this, &ARWCharacterAIBase::SetDead);

	HpBarComp = CreateDefaultSubobject<UHpBarWidgetComponent>(TEXT("Widget Component"));
	HpBarComp->SetupAttachment(GetMesh());
	HpBarComp->SetRelativeLocation(FVector(0.f, 0.f, -50.f));

	static ConstructorHelpers::FClassFinder<UHpBarBaseWidget> HpBarBaseWidgetRef(TEXT("/Game/UI/WBP_HpBar.WBP_HpBar_C"));
	if (HpBarBaseWidgetRef.Class)
	{
		HpBarBaseWidget = HpBarBaseWidgetRef.Class;
		HpBarComp->SetWidgetClass(HpBarBaseWidget);
		HpBarComp->SetWidgetSpace(EWidgetSpace::Screen);
		HpBarComp->SetDrawSize(FVector2D(150.f, 15.f));
		HpBarComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	NiagaraComp->SetupAttachment(GetMesh());
	NiagaraComp->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	NiagaraComp->bAutoActivate = false;
}

void ARWCharacterAIBase::BeginPlay()
{
	Super::BeginPlay();

}

void ARWCharacterAIBase::SetAttackFinishedDelegate(const FOnAttackFinished& InOnAttackFinished)
{
    OnAttackFinished = InOnAttackFinished;
}

void ARWCharacterAIBase::AttackByAI()
{
}

float ARWCharacterAIBase::GetAttackRange()
{
    return 200.f;
}

float ARWCharacterAIBase::GetTurnSpeed()
{
    return 2.f;
}

void ARWCharacterAIBase::SetupHpBarWidget(UHpBarWidget* InHpBarWidget)
{
	if (InHpBarWidget)
	{
		InHpBarWidget->SetMaxHp(StatComp->GetTotalStat().MaxHp);
		InHpBarWidget->UpdateHpBar(StatComp->GetTotalStat().MaxHp);
		StatComp->OnHpChanged.AddUObject(InHpBarWidget, &UHpBarWidget::UpdateHpBar);
	}
}

float ARWCharacterAIBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float SuperResult = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	StatComp->ApplyDamage(Damage);

	return 0.0f;
}

bool ARWCharacterAIBase::CheckDeath() const
{
	return StatComp->GetCurrentHp() <= 0.f;
}

void ARWCharacterAIBase::SetDead()
{
	ARWInGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ARWInGameModeBase>();
	if (GameMode != nullptr)
	{
		GameMode->PawnKilled(this);
	}
}

void ARWCharacterAIBase::RunParticle()
{
	if (NiagaraComp->IsActive())
	{
		NiagaraComp->Deactivate();
	}
	NiagaraComp->SetActive(true);
}
