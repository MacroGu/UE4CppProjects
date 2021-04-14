// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ExCharacterEntity.h"
#include "Center/ExMmoGameMode.h"
#include "Engine/KBEngine.h"
#include "Engine/Entity.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"


// Sets default values
AExCharacterEntity::AExCharacterEntity()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HP = 500;
}

// Called when the game starts or when spawned
void AExCharacterEntity::BeginPlay()
{
	Super::BeginPlay();
	
	// ����������
	if (!IsPlayer && MmoGameMode)
	{
		MmoGameMode->CharacterMap.Add(EntityId, this);
	}

	// ��ʼ������
	LastUpdatePositionTime = GetWorld()->TimeSeconds;
	LastUpdateAnimTime = GetWorld()->TimeSeconds;

	// ��ȡ������ͼ
	CharacterAnim = GetMesh()->GetAnimInstance();

	// ˢ��һ��ʵ�����ݵ�UE4 ����
	KBEngine::Entity* EntityInst = KBEngine::KBEngineApp::getSingleton().findEntity(EntityId);
	if (EntityInst)
	{
		EntityInst->callPropertysSetMethods();
	}

}

void AExCharacterEntity::Destroyed()
{
	Super::Destroyed();

	// ����������
	if (!IsPlayer && MmoGameMode)
	{
		MmoGameMode->CharacterMap.Remove(EntityId);
	}
}

void AExCharacterEntity::SetTargetPosition(FVector InPos)
{
	TargetPosition = InPos;

	// ��ȡ����ʱ����
	float UpdatePositionSpaceTime = GetWorld()->TimeSeconds - LastUpdatePositionTime;
	// ���浱ǰʱ��
	LastUpdatePositionTime = GetWorld()->TimeSeconds;
	// ��ȡ����
	float Distance = FVector::Dist(TargetPosition, GetActorLocation());
	// �����ʵʱ�ٶ�
	MoveSpeed = Distance / UpdatePositionSpaceTime;

}

void AExCharacterEntity::SetTargetRotator(FRotator InRot)
{
	TargetRotator = InRot;
}

void AExCharacterEntity::SetTargetAnim(float Speed, float Direction)
{
	// ��ȡ��ֵͷβ״̬
	TargetSpeed = Speed;
	TargetDirection = Direction;
	LastSpeed = AnimSpeed;
	LastDirection = AnimDirection;

	// ��ȡʱ����
	UpdateAnimSpaceTime = GetWorld()->TimeSeconds - LastUpdateAnimTime;
	RemainAnimSpaceTime = UpdateAnimSpaceTime;
	// ������һ�θ��µ�ʱ��
	LastUpdateAnimTime = GetWorld()->TimeSeconds;

}

void AExCharacterEntity::OnAttack()
{
	if (CharacterAnim)
	{
		CharacterAnim->Montage_Play(AttackMontage);
	}
}
