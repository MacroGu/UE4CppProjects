// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiThirdSlAiPlayerAnim.h"
#include "SlAiPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SlAiHelper.h"


USlAiThirdSlAiPlayerAnim::USlAiThirdSlAiPlayerAnim()
{
	// ������ֵ
	Direction = 0.f;
	// ���Ƿ��ڿ��и�ֵ
	IsInAir = false;
}

void USlAiThirdSlAiPlayerAnim::UpdateParameter()
{
	Super::UpdateParameter();

	// ���������ֱ�ӷ��أ� �����ָ������ն�
	if (!SPCharacer) return;
	// ��ȡ�Ƿ�����Ծ
	IsInAir = SPCharacer->GetCharacterMovement()->IsFalling();
	// �ٶȳ����Yaw��ת��ȥActor������ʵ��������������Yaw��ת�õ���Է���
	float PreDir = SPCharacer->GetVelocity().ToOrientationRotator().Yaw - SPCharacer->GetActorRotation().Yaw;
	
	// ���һ������
	SlAiHelper::Debug(FString("SPCharacter->Velocity : ") + FString::SanitizeFloat(SPCharacer->GetVelocity().ToOrientationRotator().Yaw), 0.f);
	SlAiHelper::Debug(FString("SPCharacer : ") + FString::SanitizeFloat(SPCharacer->GetActorRotation().Yaw), 0.f);
	SlAiHelper::Debug(FString("PreDir : ") + FString::SanitizeFloat(PreDir), 0.f);

	if (PreDir > 180.f)	PreDir -= 360.f;
	if (PreDir < -180.f) PreDir += 360.f;

	Direction = PreDir;


	SlAiHelper::Debug(FString("Direction : ") + FString::SanitizeFloat(Direction), 0.f);
}
