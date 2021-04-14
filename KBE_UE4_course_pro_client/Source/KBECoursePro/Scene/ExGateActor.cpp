// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/ExGateActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Player/ExPlayerCharacter.h"
#include "Scripts/ExCommon.h"
#include "Engine/KBEngine.h"
#include "Kismet/GameplayStatics.h"
#include "Scripts/ExEventData.h"




AExGateActor::AExGateActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	GateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateMesh"));
	GateMesh->SetupAttachment(RootComponent);

	GateWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("GateWidget"));
	GateWidget->SetupAttachment(RootComponent);

	GateBox = CreateDefaultSubobject<UBoxComponent>(TEXT("GateBox"));
	GateBox->SetupAttachment(RootComponent);

	FScriptDelegate OverlayBegin;
	OverlayBegin.BindUFunction(this, "OnOverlayBegin");
	GateBox->OnComponentBeginOverlap.Add(OverlayBegin);
}

void AExGateActor::BeginPlay()
{
	Super::BeginPlay();
	// ��ʼ��ʱ��͸������ֵ�UI
	UpdateRoomName(FText::FromString(RoomName));
}

void AExGateActor::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �������ң�ֱ�Ӵ���������ת
	AExPlayerCharacter* PlayerCharacter = Cast<AExPlayerCharacter>(OtherActor);

	if (PlayerCharacter)
	{
		UKBEventData_ReqTeleportRoom* EventData = NewObject<UKBEventData_ReqTeleportRoom>();
		EventData->DesRoomId = RoomId;
		KBENGINE_EVENT_FIRE("ReqTeleportRoom", EventData);
	}


}

void AExGateActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// ����Ѫ������
	FVector CameraPos = UExCommon::Get()->GetCameraPos();
	FVector StartPos(GetActorLocation().X, GetActorLocation().Y, 0);
	FVector TargetPos(CameraPos.X, CameraPos.Y, 0.f);
	GateWidget->SetWorldRotation(FRotationMatrix::MakeFromX(TargetPos - StartPos).Rotator());
}
