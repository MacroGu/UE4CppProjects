// Fill out your copyright notice in the Description page of Project Settings.


#include "FireEffectActor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/TextRenderComponent.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"



// Sets default values
AFireEffectActor::AFireEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));

	FireEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireEffect"));
	FireEffect->SetupAttachment(RootComponent);

	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
	TextRender->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AFireEffectActor::BeginPlay()
{
	Super::BeginPlay();

	CountDownTimer = 20;

	// ����Ƿ����
	if (GetWorld()->IsServer())
	{
		// ѭ������
		FTimerDelegate UpdateTimerDele = FTimerDelegate::CreateUObject(this, &AFireEffectActor::UpdateTimer);
		GetWorld()->GetTimerManager().SetTimer(UpdateTimeHandle, UpdateTimerDele, 1.f, true);
	}
	
}

// Called every frame
void AFireEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ��Ⱦ����
	TextRender->SetText(FString::FromInt(CountDownTimer));

}

void AFireEffectActor::UpdateTimer()
{
	if (CountDownTimer > 0)
	{
		CountDownTimer -= 1;
	}
	else
	{
		Deactivate = !Deactivate;
		OnRep_Deactivate();
	}

}

void AFireEffectActor::OnRep_Deactivate()
{
	FireEffect->Deactivate();
}

// ��Ҫ���� Replicated ����ı����������������д�½���ע��
void AFireEffectActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFireEffectActor, CountDownTimer);

	DOREPLIFETIME(AFireEffectActor, Deactivate);
}

