// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiHandNone.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"



ASlAiHandNone::ASlAiHandNone()
{
	// ����ģ��

	// ������ײ������
	AffectionCollision->SetBoxExtent(FVector(10.f, 10.f, 10.f));
	AffectionCollision->SetRelativeLocation(FVector(0.f, 0.f, 10.f));
}

void ASlAiHandNone::BeginPlay()
{
	Super::BeginPlay();

	// ������Ʒ���
	ObjectIndex = 0;
}
