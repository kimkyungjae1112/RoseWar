// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/ArrowReleaseNotify.h"
#include "Interface/BowAttackCheckInterface.h"

void UArrowReleaseNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp->GetOwner())
	{
		IBowAttackCheckInterface* Interface = Cast<IBowAttackCheckInterface>(MeshComp->GetOwner());
		if (Interface)
		{
			Interface->ReleaseArrow();
		}
	}
}
