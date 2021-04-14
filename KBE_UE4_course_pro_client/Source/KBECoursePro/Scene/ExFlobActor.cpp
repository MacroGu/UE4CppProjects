// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/ExFlobActor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/StaticMeshComponent.h"
#include "Center/ExMmoGameMode.h"
#include "Data/ExDataMgr.h"



AExFlobActor::AExFlobActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);
}

void AExFlobActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// ��תģ��
	BaseMesh->AddLocalRotation(FRotator(DeltaSeconds * 100.f, 0.f, 0.f));

}

void AExFlobActor::Destroyed()
{
	Super::Destroyed();

	// ��GameMode �Ƴ�
	if (MmoGameMode)
	{
		MmoGameMode->FlobMap.Remove(EntityId);
	}
}

void AExFlobActor::BeginPlay()
{
	Super::BeginPlay();

	if (MmoGameMode)
	{
		MmoGameMode->FlobMap.Add(EntityId, this);
	}

	// ���ɲ��ʣ���ȡ��ͼ���������
	UTexture* GoodTexture = UExDataMgr::Get()->GetGoodTexture(GoodId);

	// ���ɲ���
	BaseMatInst = UMaterialInstanceDynamic::Create(BaseMat, NULL);
	BaseMatInst->SetTextureParameterValue(FName("BaseTex"), GoodTexture);

	BaseMesh->SetMaterial(0, BaseMatInst);

}
