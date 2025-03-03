// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/SwordAttackCheckNotifyState.h"
#include "Interface/SwordAttackCheckInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Engine/DamageEvents.h"

USwordAttackCheckNotifyState::USwordAttackCheckNotifyState()
{
}

void USwordAttackCheckNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

}

void USwordAttackCheckNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (MeshComp->GetOwner())
	{
		MakeLineTrace(MeshComp->GetOwner());
	}
}

void USwordAttackCheckNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	Hits.Empty();
}

void USwordAttackCheckNotifyState::MakeLineTrace(AActor* Character)
{
	ISwordAttackCheckInterface* Interface = Cast<ISwordAttackCheckInterface>(Character);
	if (Interface)
	{
		USkeletalMeshComponent* SwordMeshComp = Interface->GetSwordBone();
		if (SwordMeshComp)
		{
			FVector SwordBoneStart = SwordMeshComp->GetSocketLocation(TEXT("SwordBoneStart"));
			FVector SwordBoneEnd = SwordMeshComp->GetSocketLocation(TEXT("SwordBoneEnd"));

			FHitResult HitResult;
			FCollisionQueryParams Params(NAME_None, false, Character);
			UWorld* World = Character->GetWorld();
			check(World);

			IGenericTeamAgentInterface* TeamInterface = Cast<IGenericTeamAgentInterface>(Character);
			check(TeamInterface);

			bool bHit = World->LineTraceSingleByChannel(
				HitResult, 
				SwordBoneStart, 
				SwordBoneEnd, 
				TeamInterface->GetGenericTeamId() != FGenericTeamId(0) ? ECC_GameTraceChannel1 : ECC_GameTraceChannel2, 
				Params
			);

			//DrawDebugLine(World, SwordBoneStart, SwordBoneEnd, FColor::Red, false, 3.f);

			if (bHit && !Hits.Contains(HitResult.GetActor()))
			{
				Hits.Add(HitResult.GetActor());

				if (HitResult.GetActor())
				{
					APawn* Instigator = Cast<APawn>(Character);
					FDamageEvent DamageEvent;
					HitResult.GetActor()->TakeDamage(100.f, DamageEvent, Instigator->GetController(), Character);

					DrawDebugSphere(World, HitResult.ImpactPoint, 15.f, 32, FColor::Green, false, 3.f);
				}
			}
		}
	}
}
