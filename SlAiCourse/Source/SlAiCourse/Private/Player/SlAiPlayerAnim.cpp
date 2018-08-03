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
}

void USlAiPlayerAnim::UpdateMontage()
{
	// ���������ֱ�ӷ��أ� �����ָ������ն�
	if (!SPCharacer) return;
	if (!Montage_IsPlaying(PlayerPunchMontage))
	{
		Montage_Play(PlayerPunchMontage);
	}

}
