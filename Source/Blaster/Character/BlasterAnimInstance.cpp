// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BlasterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BlasterCharacter.h"
#include "BlasterComponents/CombatComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Weapon/Weapon.h"

void UBlasterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	BlasterCharacter = Cast<ABlasterCharacter>(TryGetPawnOwner());
}

void UBlasterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if(BlasterCharacter == nullptr)
	{
		BlasterCharacter = Cast<ABlasterCharacter>(TryGetPawnOwner());
	}
	if(BlasterCharacter == nullptr) return;

	FVector Velocity = BlasterCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = BlasterCharacter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = BlasterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0 ? true : false;
	bWeaponEquipped = BlasterCharacter->IsWeaponEquipped();
	EquippedWeapon = BlasterCharacter->GetEquippedWeapon();
	bIsCrouched= BlasterCharacter->bIsCrouched;
	bAiming = BlasterCharacter->IsAiming();
	TurningInPlace = BlasterCharacter->GetTurningInPlace();
	bRotateRootBone = BlasterCharacter->ShouldRotateRootBone();
	bElimmed = BlasterCharacter->IsElimmed();
	bHoldingTheFlag = BlasterCharacter->IsHoldingTheFlag();
	
	// Offset Yaw
	FRotator AimRotation = BlasterCharacter->GetBaseAimRotation();
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(BlasterCharacter->GetVelocity());
	FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation);
	DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaTime, 6.f);
	YawOffset = DeltaRotation.Yaw;

	CharacterRotationLastFrame = CharacterRotation;
	CharacterRotation = BlasterCharacter->GetActorRotation();
	const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame);
	const float Target = Delta.Yaw / DeltaTime;
	const float Interp = FMath::FInterpTo(Lean, Target, DeltaTime, 6.f);
	Lean = FMath::Clamp(Interp, -90.f, 90.f);

	AO_Yaw = BlasterCharacter->GetAO_Yaw();
	AO_Pitch = BlasterCharacter->GetAO_Pitch();

	
	if (bWeaponEquipped && EquippedWeapon && EquippedWeapon->GetWeaponMesh() && BlasterCharacter->GetMesh())
	{
		// 무기를 왼손으로 잡는 부분을 메쉬에 소켓으로 추가하고 그 부분을 WorldSpace의 Transform값으로 가져온다. 
		LeftHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("LeftHandSocket"), ERelativeTransformSpace::RTS_World);
		FVector OutPosition;
		FRotator OutRotation;
		// TransformToBoneSpace 함수로 hand_r 뼈의 Transform 을 OutPosition과 OutRotation에 위치와 회전 저장
		BlasterCharacter->GetMesh()->TransformToBoneSpace(FName("hand_r"), LeftHandTransform.GetLocation(), FRotator::ZeroRotator, OutPosition, OutRotation);

		// hand_r뼈의 위치와 회전값을 무기 Mesh의 소켓인 LeftHandSocket값에 적용하여 동일한 값을 가지게함
		LeftHandTransform.SetLocation(OutPosition);
		LeftHandTransform.SetRotation(FQuat(OutRotation));

		if (BlasterCharacter->IsLocallyControlled())
		{
			bLocallyControlled = true;
			FTransform RightHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("hand_r"), ERelativeTransformSpace::RTS_World);
			FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(RightHandTransform.GetLocation(), RightHandTransform.GetLocation() + (RightHandTransform.GetLocation() - BlasterCharacter->GetHitTarget()));
			RightHandRotation = FMath::RInterpTo(RightHandRotation, LookAtRotation, DeltaTime, 30.f);
		}
	}

	
	bUseFABRIK = BlasterCharacter->GetCombatState() == ECombatState::ECS_Unoccupied;
	bool bFABRIKOverride = BlasterCharacter->IsLocallyControlled() &&
		BlasterCharacter->GetCombatState() != ECombatState::ECS_ThrowingGrenade;
	if(bFABRIKOverride)
	{
		bUseFABRIK = !BlasterCharacter->IsLocallyReloading() && BlasterCharacter->bFinishedSwapping;
	}
	bUseAimOffsets = BlasterCharacter->GetCombatState() == ECombatState::ECS_Unoccupied && !BlasterCharacter->GetDisableGameplay();
	bTransformRightHand = BlasterCharacter->GetCombatState() == ECombatState::ECS_Unoccupied && !BlasterCharacter->GetDisableGameplay();

	
}

void UBlasterAnimInstance::AnimNotify_ReloadFinished()
{
	if(BlasterCharacter)
	{
		if(BlasterCharacter->GetCombat())
			BlasterCharacter->GetCombat()->FinishReloading();
	}
}

void UBlasterAnimInstance::AnimNotify_Shell()
{
	if(BlasterCharacter)
	{
		if(BlasterCharacter->GetCombat())
			BlasterCharacter->GetCombat()->ShotgunShellReload();
	}
}

void UBlasterAnimInstance::AnimNotify_FinishGrenadeThrow()
{
	if(BlasterCharacter)
	{
		if(BlasterCharacter->GetCombat())
			BlasterCharacter->GetCombat()->ThrowGrenadeFinished();
	}
}

void UBlasterAnimInstance::AnimNotify_GrenadeLaunch()
{
	if(BlasterCharacter)
	{
		if(BlasterCharacter->GetCombat())
			BlasterCharacter->GetCombat()->LaunchGrenade();
	}
}

void UBlasterAnimInstance::AnimNotify_SwapAttachWeapons()
{
	if(BlasterCharacter)
	{
		if(BlasterCharacter->GetCombat())
			BlasterCharacter->GetCombat()->FinishSwapAttachWeapons();
	}
}

void UBlasterAnimInstance::AnimNotify_SwapFinished()
{
	if(BlasterCharacter)
	{
		if(BlasterCharacter->GetCombat())
			BlasterCharacter->GetCombat()->FinishSwap();
	}
}
