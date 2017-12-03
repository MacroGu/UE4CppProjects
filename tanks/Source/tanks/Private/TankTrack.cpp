// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTrack();
	ThrottleToDrive = 0;
	ApplySideForce();
}

void UTankTrack::SetThrottle(float Throttle)
{
	ThrottleToDrive = FMath::Clamp<float>(ThrottleToDrive + Throttle, -1,1);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = TankMaDrivingForce * ThrottleToDrive * GetForwardVector();
	auto ForceLocation = GetSocketLocation(FName("ForceLocation"));
	auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	RootComponent->AddForceAtLocation(ForceApplied,ForceLocation);
}

void UTankTrack::ApplySideForce()
{
	auto RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	// �ҵ�̹�˵��ƶ����� ���ٶ�
	auto TankVelocity = RootComponent->GetComponentVelocity();
	auto RightVector = RootComponent->GetRightVector();
	// �ҵ� ̹�˲໬���ٶ�
	auto SideSpeed = FVector::DotProduct(RightVector, TankVelocity);
	
	float DeltaTime = GetWorld()->DeltaTimeSeconds;
	// �ҵ�̹�˲໬��Ӧ�ļ��ٶ�
	auto SideSpeedAcceleration = -SideSpeed / DeltaTime * GetRightVector();

	// F = ma
	auto CorrectionForce = (RootComponent->GetMass() * SideSpeedAcceleration) / 2;
	RootComponent->AddForce(CorrectionForce);

}
