// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ExRemoteCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Animation/AnimInstance.h"
#include "Scripts/ExCommon.h"
#include "HUD/ExBloodBar.h"


FName AExRemoteCharacter::GroundName(TEXT("Ground"));

AExRemoteCharacter::AExRemoteCharacter()
{
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	BloodBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("BloodBar"));
	BloodBarComponent->SetupAttachment(RootComponent);


	GroundBox = CreateDefaultSubobject<UBoxComponent>(TEXT("GroundBox"));
	GroundBox->SetupAttachment(RootComponent);
	GroundBox->SetCollisionProfileName(FName("OverlapAll"));

	FScriptDelegate OverlapBegin;
	OverlapBegin.BindUFunction(this, "OnOverlapBegin");
	GroundBox->OnComponentBeginOverlap.Add(OverlapBegin);

	FScriptDelegate OverlapEnd;
	OverlapEnd.BindUFunction(this, "OnOverlapEnd");
	GroundBox->OnComponentEndOverlap.Add(OverlapEnd);

}

void AExRemoteCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// λ�ø���
	FVector CurrentPosition = GetActorLocation();

	FVector MoveDirection = TargetPosition - CurrentPosition;

	float DeltaSpace = DeltaSeconds * MoveSpeed;

	float Distance = MoveDirection.Size();

	// ����̫�����̫С��ֱ������λ��
	if (Distance > 100.f || Distance < DeltaSpace)
	{
		SetActorLocation(TargetPosition);
	}
	else
	{
		// �ƶ�λ��
		MoveDirection.Normalize();
		SetActorLocation(CurrentPosition + MoveDirection * DeltaSpace);
	}

	// ��ת����
	FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), TargetRotator, DeltaSeconds, 5.f);
	FaceRotation(CurrentRotation);

	// ���¶���
	RemainAnimSpaceTime -= DeltaSeconds * 5;
	float AnimLerpPercent = FMath::Clamp(RemainAnimSpaceTime / UpdateAnimSpaceTime, 0.f, 1.f);
	AnimSpeed = FMath::Lerp(TargetSpeed, LastSpeed, AnimLerpPercent);
	AnimDirection = FMath::Lerp(TargetDirection, LastDirection, AnimLerpPercent);

	// ����Ѫ������
	FVector CameraPos = UExCommon::Get()->GetCameraPos();
	FVector StartPos(GetActorLocation().X, GetActorLocation().Y, 0);
	FVector TargetPos(CameraPos.X, CameraPos.Y, 0.f);
	BloodBarComponent->SetWorldRotation(FRotationMatrix::MakeFromX(TargetPos - StartPos).Rotator());
}

void AExRemoteCharacter::SetBaseHP(int32 InBaseHP)
{
	if (InBaseHP < BaseHP)
	{
		// �ж��Ƿ�ǰѪֵ���µ�ѪֵС
		if (HP < InBaseHP)
		{
			HP = InBaseHP;
		}
	}
	BaseHP = InBaseHP;

	float HpPercent = FMath::Clamp((float)HP / (float)BaseHP, 0.f, 1.f);
	if (BloodBar)
	{
		BloodBar->SetHpPercent(HpPercent);
	}
}

void AExRemoteCharacter::SetHP(int32 InHP)
{
	if (InHP > 0 && InHP < BaseHP && InHP != BaseHP)
	{
		// �������˶���
		CharacterAnim->Montage_Play(HurtMontage);
	}

	HP = InHP;

	float HpPercent = FMath::Clamp((float)HP / (float)BaseHP, 0.f, 1.f);
	if (BloodBar)
	{
		BloodBar->SetHpPercent(HpPercent);
	}

}

void AExRemoteCharacter::BeginPlay()
{
	Super::BeginPlay();

	// ��ȡѪ��
	BloodBar = Cast<UExBloodBar>(BloodBarComponent->GetUserWidgetObject());
	// �������ֺ�����
	BloodBar->SetRole(RoleType, RoleName);

}

void AExRemoteCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �Ƿ���������
	if (OtherActor->GetFName().IsEqual(GroundName))
	{
		AnimIsInAir = false;
	}


}

void AExRemoteCharacter::OnOverLapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// �Ƿ���������
	if (OtherActor->GetFName().IsEqual(GroundName))
	{
		AnimIsInAir = true;
	}


}
