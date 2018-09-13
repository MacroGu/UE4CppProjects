// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiPlayerAnim.h"
#include "SlAiPlayerCharacter.h"



USlAiPlayerAnim::USlAiPlayerAnim()
{
	Speed = 0.f;
	SpineRotator = FRotator(0.f,0.f,0.f);
}

void USlAiPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	// ��ʼ����ɫָ��
	InitSPCharacter();
	// ������ͼ����
	UpdateParameter();
	// ���¶���
	UpdateMontage();

}

void USlAiPlayerAnim::ChangeDetection(bool IsOpen)
{
	if (!SPCharacer) return;

	SPCharacer->ChangeHandObjectDetect(IsOpen);

}

void USlAiPlayerAnim::InitSPCharacter()
{
	if (!SPCharacer)
	{
		SPCharacer = Cast<ASlAiPlayerCharacter>(TryGetPawnOwner());
	}
}

void USlAiPlayerAnim::UpdateParameter()
{
	// ���������ֱ�ӷ��أ� �����ָ������ն�
	if (!SPCharacer) return;
	// �����ٶ�
	Speed = SPCharacer->GetVelocity().Size();
	// �����ϰ������ת
	float SpineDir = SPCharacer->GetActorRotation().Yaw - 90.f;
	if (SpineDir > 180.f) SpineDir -= 360.f;
	if (SpineDir < -180.f) SpineDir += 360.f;
	SpineRotator = FRotator(0.f, SpineDir, 90.f);
}

void USlAiPlayerAnim::UpdateMontage()
{
	// ���������ֱ�ӷ��أ� �����ָ������ն�
	if (!SPCharacer) return;

	// �����ǰ���˳�״̬����������Ĳ�һ�£�ֱ�ӷ���
	if (SPCharacer->GameView != GameView) return;

	// �����ǰ����û��ֹͣ�������¶���
	if (!Montage_GetIsStopped(CurrentMontage)) return;
	
	switch (SPCharacer->UpperType)
	{
	case EUpperBody::None:
		if (CurrentMontage != nullptr)
		{
			Montage_Stop(0);
			CurrentMontage = nullptr;
			// �����л��ӽ�
			AllowViewChange(true);
		}
		break;
	case EUpperBody::Punch:
		if (!Montage_IsPlaying(PlayerPunchMontage))
		{
			Montage_Play(PlayerPunchMontage);
			CurrentMontage = PlayerPunchMontage;
			// �������л��ӽ�
			AllowViewChange(false);
		}
		break;
	case EUpperBody::Hit:
		if (!Montage_IsPlaying(PlayerHitMontage))
		{
			Montage_Play(PlayerHitMontage);
			CurrentMontage = PlayerHitMontage;
			AllowViewChange(false);
		}
		break;
	case EUpperBody::Fight:
		if (!Montage_IsPlaying(PlayerFightMontage))
		{
			Montage_Play(PlayerFightMontage);
			CurrentMontage = PlayerFightMontage;
			AllowViewChange(false);
		}
		break;
	case EUpperBody::PickUp:
		if (!Montage_IsPlaying(PlayerPickUpMontage))
		{
			Montage_Play(PlayerPickUpMontage);
			CurrentMontage = PlayerPickUpMontage;
			AllowViewChange(false);
		}
		break;
	case EUpperBody::Eat:
		if (!Montage_IsPlaying(PlayerEatMontage))
		{
			Montage_Play(PlayerEatMontage);
			CurrentMontage = PlayerEatMontage;
			AllowViewChange(false);
		}
		break;
	default:
		break;
	}
	
}

void USlAiPlayerAnim::AllowViewChange(bool IsAllow)
{
	if (!SPCharacer) return;
	SPCharacer->IsAllowSwitch = IsAllow;
}
