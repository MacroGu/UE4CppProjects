// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/ExSkillActor.h"
#include "Center/ExMmoGameMode.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/World.h"
#include "Components/AudioComponent.h"



AExSkillActor::AExSkillActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));

	// ʵ��������������Ч���
	SkillParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SkillParticleComponent"));
	SkillParticleComponent->SetupAttachment(RootComponent);

	ShootAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("ShootAudio"));
	ShootAudio->SetupAttachment(RootComponent);

	ExplodeAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("ExplodeAudio"));
	ExplodeAudio->SetupAttachment(RootComponent);

}

void AExSkillActor::Destroyed()
{
	Super::Destroyed();

	if (MmoGameMode)
	{
		MmoGameMode->SkillMap.Remove(EntityId);
	}

}

void AExSkillActor::PlayExplode()
{
	// ���ű�ը��Ч
	SkillParticleComponent->SetTemplate(ExplodeParticle);

	// ���ű�ը��Ч
	ExplodeAudio->Play();

	// ��ʱ 1.5 ������
	GetWorld()->GetTimerManager().SetTimer(DestroyHandle, this, &AExSkillActor::DestroySkill, 1.5f);

}

void AExSkillActor::BeginPlay()
{
	Super::BeginPlay();

	if (MmoGameMode)
	{
		MmoGameMode->SkillMap.Add(EntityId, this);
	}

	// һ��ʼ�Ͳ��ż�����Ч
	SkillParticleComponent->SetTemplate(SkillParticle);

	// ��������
	ShootAudio->Play();

}

void AExSkillActor::DestroySkill()
{
	Destroy();
}
