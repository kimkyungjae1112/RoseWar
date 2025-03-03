// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RWCharacterBase.h"
#include "InputActionValue.h"
#include "Interface/HUDInterface.h"
#include "Interface/SwordAttackCheckInterface.h"
#include "RWCharactePlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class URWInputData;
class APlayerController;
class UHUDWidget;
class URWStatComponent;
class ARWPlayerController;
class UAnimInstance;
class UAnimMontage;
class URWComboAttackData;
class UMotionWarpingComponent;

UCLASS()
class ROSEWAR_API ARWCharactePlayer : public ARWCharacterBase, public IHUDInterface, public ISwordAttackCheckInterface
{
	GENERATED_BODY()

public:
	ARWCharactePlayer();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* HUD Interface Implement */
	virtual void SetHUDWidget(UHUDWidget* InHUDWidget) override;

	/* IGenericTeamAgentInterface Implement */
	virtual FGenericTeamId GetGenericTeamId() const override;

	/* ISwordAttackCheckInterface Implement */
	virtual USkeletalMeshComponent* GetSwordBone() override;

protected:
	virtual void BeginPlay() override;

/* Utility */
private:
	APlayerController* GetPlayerController();
	ARWPlayerController* GetMyPlayerController();

/* Camera */
private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComp;

/* Input */
private:
	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<URWInputData> InputData;

/* Damaged */
public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

/* Ability */
private:
	void Move(const FInputActionValue& Value);
	void Walk();
	void Run();

	void Look(const FInputActionValue& Value);
	void DisplayCommandWindow();
	void Interact();

	void SetDead();
	

	void Attack();
	void BeginDefaultAttack();
	void EndDefaultAttack(class UAnimMontage* Target, bool IsProperlyEnded);
	void SetComboCheckTimer();
	void ComboCheck();

	int32 CurrentCombo = 0;
	FTimerHandle ComboTimerHandle;
	bool HasNextComboAttack = false;


/* Data */
private:
	UPROPERTY(VisibleAnywhere, Category = "Data")
	TObjectPtr<URWComboAttackData> ComboData;

///* State */
//public:
//	virtual void SetState(FCharacterState* InState) { State = InState; }
//
//private:
//	void ProcessInput();
//
//	FCharacterState* State;
	/*virtual float GetMovingSpeed() override;
	virtual void Walk() override;
	virtual void Run() override;*/


	/* UI */
private:
	UPROPERTY(VisibleAnywhere, Category = "UI")
	TObjectPtr<UHUDWidget> HUDWidget;

/* Component */
private:
	UPROPERTY(VisibleAnywhere, Category = "Stat")
	TObjectPtr<URWStatComponent> StatComp;

	UPROPERTY(VisibleAnywhere, Category = "MotionWarp")
	TObjectPtr<UMotionWarpingComponent> MotionWarpComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> HeadMeshComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> HairMeshComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> EyeMeshComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> HandMeshComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> LegMeshComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> FeetMeshComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> LeftWeaponMeshComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> RightWeaponMeshComp;

/* Animation */
private:
	UPROPERTY(VisibleAnywhere, Category = "Animation")
	TObjectPtr<UAnimInstance> Anim;

	UPROPERTY(EditAnywhere, Category = "Animation")
	TObjectPtr<UAnimMontage> Sword2HAttackMontage;

	UPROPERTY(EditAnywhere, Category = "Animation")
	TObjectPtr<UAnimMontage> MountMontage;
};