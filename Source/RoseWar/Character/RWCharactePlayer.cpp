// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RWCharactePlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Data/RWInputData.h"
#include "Component/RWPlayerStatComponent.h"
#include "UI/HUDWidget.h"
#include "Player/RWPlayerController.h"
#include "Interact/RWHorse.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Data/RWComboAttackData.h"
#include "MotionWarpingComponent.h"
#include "RoseWar.h"

ARWCharactePlayer::ARWCharactePlayer()
{
	ClassName = TEXT("Player");

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->TargetArmLength = 650.f;
	SpringArmComp->bDoCollisionTest = false;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	HeadMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Head"));
	HeadMeshComp->SetupAttachment(GetMesh());
	HeadMeshComp->SetLeaderPoseComponent(GetMesh());

	HairMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hair"));
	HairMeshComp->SetupAttachment(GetMesh());
	HairMeshComp->SetLeaderPoseComponent(GetMesh());

	EyeMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Eye"));
	EyeMeshComp->SetupAttachment(GetMesh());
	EyeMeshComp->SetLeaderPoseComponent(GetMesh());

	HandMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hand"));
	HandMeshComp->SetupAttachment(GetMesh());
	HandMeshComp->SetLeaderPoseComponent(GetMesh());

	LegMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Leg"));
	LegMeshComp->SetupAttachment(GetMesh());
	LegMeshComp->SetLeaderPoseComponent(GetMesh());

	FeetMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Feet"));
	FeetMeshComp->SetupAttachment(GetMesh());
	FeetMeshComp->SetLeaderPoseComponent(GetMesh());

	LeftWeaponMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Weapon"));
	LeftWeaponMeshComp->SetupAttachment(GetMesh(), TEXT("hand_lSocket"));

	RightWeaponMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Weapon"));
	RightWeaponMeshComp->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/MRPGT/SkeletalMeshes/Humans/PlateArmour_C/SK_Plate_Torso_C_3_Green.SK_Plate_Torso_C_3_Green'"));
	if (BodyMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(BodyMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<URWInputData> InputDataRef(TEXT("/Script/RoseWar.RWInputData'/Game/Data/DA_InputData.DA_InputData'"));
	if (InputDataRef.Object)
	{
		InputData = InputDataRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<URWComboAttackData> ComboDataRef(TEXT("/Script/RoseWar.RWComboAttackData'/Game/Data/DA_ComboData.DA_ComboData'"));
	if (ComboDataRef.Object)
	{
		ComboData = ComboDataRef.Object;
	}

	StatComp = CreateDefaultSubobject<URWPlayerStatComponent>(TEXT("Stat Component"));
	StatComp->OnHpZero.AddUObject(this, &ARWCharactePlayer::SetDead);

	MotionWarpComp = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarping"));

	TeamId = FGenericTeamId(0);
	Tags.Add(TEXT("Commander"));

	Walk();
}

void ARWCharactePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(InputData->MoveAction, ETriggerEvent::Triggered, this, &ARWCharactePlayer::Move);
	EnhancedInputComponent->BindAction(InputData->LookAction, ETriggerEvent::Triggered, this, &ARWCharactePlayer::Look);
	EnhancedInputComponent->BindAction(InputData->JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(InputData->JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(InputData->CommandWindowAction, ETriggerEvent::Started, this, &ARWCharactePlayer::DisplayCommandWindow);
	EnhancedInputComponent->BindAction(InputData->InteractAction, ETriggerEvent::Started, this, &ARWCharactePlayer::Interact);
	EnhancedInputComponent->BindAction(InputData->RunAction, ETriggerEvent::Started, this, &ARWCharactePlayer::Run);
	EnhancedInputComponent->BindAction(InputData->RunAction, ETriggerEvent::Completed, this, &ARWCharactePlayer::Walk);
	EnhancedInputComponent->BindAction(InputData->AttackAction, ETriggerEvent::Started, this, &ARWCharactePlayer::Attack);
}

void ARWCharactePlayer::SetHUDWidget(UHUDWidget* InHUDWidget)
{
	HUDWidget = InHUDWidget;
}

FGenericTeamId ARWCharactePlayer::GetGenericTeamId() const
{
	return TeamId;
}

USkeletalMeshComponent* ARWCharactePlayer::GetSwordBone()
{
	return RightWeaponMeshComp;
}

void ARWCharactePlayer::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetPlayerController()->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputData->DefaultInputMappingContext, 0);
	}

	Anim = GetMesh()->GetAnimInstance();
	ensure(Anim);

	if (HUDWidget)
	{
		HUDWidget->SetMaxHp(StatComp->GetTotalStat().MaxHp);
		HUDWidget->UpdateHpBar(StatComp->GetTotalStat().MaxHp);
		HUDWidget->SetMoney(StatComp->GetCurrentMoney());
		StatComp->OnHpChanged.AddUObject(HUDWidget, &UHUDWidget::UpdateHpBar);
	}
}

APlayerController* ARWCharactePlayer::GetPlayerController()
{
	return Cast<APlayerController>(GetController());
}

ARWPlayerController* ARWCharactePlayer::GetMyPlayerController()
{
	return Cast<ARWPlayerController>(GetPlayerController());
}

float ARWCharactePlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float SuperResult = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	StatComp->ApplyDamage(Damage);

	return 0.0f;
}

void ARWCharactePlayer::Move(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	FRotator Rotator = GetControlRotation();
	FRotator YawRotator(0.f, Rotator.Yaw, 0.f);

	FVector ForwardVector = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
	FVector RightVector = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::Y);
	
	AddMovementInput(ForwardVector, InputValue.X);
	AddMovementInput(RightVector, InputValue.Y);
}

void ARWCharactePlayer::Walk()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

void ARWCharactePlayer::Run()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void ARWCharactePlayer::Look(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	AddControllerPitchInput(InputValue.X * 0.5f);
	AddControllerYawInput(-InputValue.Y * 0.5f);
}

void ARWCharactePlayer::DisplayCommandWindow()
{
	if (HUDWidget->GetIsOnCommandWidget())
	{
		GetMyPlayerController()->HiddenCommandWidget();
		return;
	}

	GetMyPlayerController()->DisplayCommandWidget();
}

void ARWCharactePlayer::Interact()
{
	if (GetMyPlayerController()->IsInViewportInteractWidget())
	{
		ARWHorse* Horse = Cast<ARWHorse>(UGameplayStatics::GetActorOfClass(GetWorld(), ARWHorse::StaticClass()));
		Horse->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		Anim->Montage_Play(MountMontage);
		
	}
}

void ARWCharactePlayer::SetDead()
{
	// Dead
}

void ARWCharactePlayer::Attack()
{
	if (CurrentCombo == 0)
	{
		BeginDefaultAttack();
		return;
	}

	if (!ComboTimerHandle.IsValid())
	{
		HasNextComboAttack = false;
	}
	else
	{
		HasNextComboAttack = true;
	}
}

void ARWCharactePlayer::BeginDefaultAttack()
{
	CurrentCombo = 1;
	Anim->Montage_Play(Sword2HAttackMontage);

	FOnMontageEnded MontageEnded;
	MontageEnded.BindUObject(this, &ARWCharactePlayer::EndDefaultAttack);
	Anim->Montage_SetEndDelegate(MontageEnded, Sword2HAttackMontage);

	ComboTimerHandle.Invalidate();
	SetComboCheckTimer();
}

void ARWCharactePlayer::EndDefaultAttack(UAnimMontage* Target, bool IsProperlyEnded)
{
	ensure(CurrentCombo != 0);
	CurrentCombo = 0;
}

void ARWCharactePlayer::SetComboCheckTimer()
{
	int32 ComboIndex = CurrentCombo - 1;
	ensure(ComboData->EffectiveFrameCount.IsValidIndex(ComboIndex));

	float ComboEffectiveTime = (ComboData->EffectiveFrameCount[ComboIndex] / ComboData->FrameRate);
	if (ComboEffectiveTime > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &ARWCharactePlayer::ComboCheck, ComboEffectiveTime, false);
	}
}

void ARWCharactePlayer::ComboCheck()
{
	ComboTimerHandle.Invalidate();
	if (HasNextComboAttack)
	{
		CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboData->MaxCombo);
		FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboData->SectionName, CurrentCombo);
		Anim->Montage_JumpToSection(NextSection, Sword2HAttackMontage);

		SetComboCheckTimer();
		HasNextComboAttack = false;
	}
}


