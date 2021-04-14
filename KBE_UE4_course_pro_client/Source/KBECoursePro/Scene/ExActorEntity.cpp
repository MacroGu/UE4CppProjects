// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/ExActorEntity.h"
#include "Engine/KBEngine.h"
#include "Engine/Entity.h"
#include "Center/ExMmoGameMode.h"



// Sets default values
AExActorEntity::AExActorEntity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExActorEntity::BeginPlay()
{
	Super::BeginPlay();
	
	// ����UE4 ���ӻ�ʵ�崴��Ҫ����KBE�Ĳ�����߼�ʵ�壬��KBE���ʵ����ǰ�����Ѿ�������һЩ���������¼�
	// ��˴�ʱ���ǿ��ܴ����һЩ�¼��� ����ֻ���ڴ˲��ȱ�Ҫ�Ĵ����ˣ����磺Ѫ���ٶ�����ֵ
	KBEngine::Entity* EntityInst = KBEngine::KBEngineApp::getSingleton().findEntity(EntityId);
	if (EntityInst)
	{
		EntityInst->callPropertysSetMethods();
	}

}

// Called every frame
void AExActorEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// λ�ø���
	FVector CurrentPosition = GetActorLocation();

	FVector TargetDirection = TargetPosition - CurrentPosition;

	float DeltaSpeed = DeltaTime * MoveSpeed;

	float Distance = TargetDirection.Size();

	// ����̫�����̫Сֱ������λ��
	if (Distance < DeltaSpeed)
	{
		SetActorLocation(TargetPosition);
	}
	else
	{
		// �ƶ�λ��
		TargetDirection.Normalize();
		SetActorLocation(CurrentPosition + (TargetDirection * DeltaSpeed));
	}
}

void AExActorEntity::SetTargetPosition(FVector InPos)
{
	TargetPosition = InPos;

	// ��ȡ���θ���ʱ����
	float UpdatePositionSpaceTime = GetWorld()->TimeSeconds - LastUpdatePositionTIme;
	// �����ϴθ���ʱ��
	LastUpdatePositionTIme = GetWorld()->TimeSeconds;
	// ��ȡ����
	float Distance = FVector::Dist(TargetPosition, GetActorLocation());
	// ����ʵʱ�ٶ�
	MoveSpeed = Distance / UpdatePositionSpaceTime;

}

