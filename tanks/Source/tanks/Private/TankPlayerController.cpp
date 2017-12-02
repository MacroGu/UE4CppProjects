// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();


	ATank* ControlledTank = GetControlledTank();
	if (ControlledTank == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Error, Controlled tank is null"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("controlled tank is %s"), *ControlledTank->GetName());
	}

}

void ATankPlayerController::Tick(float DelatTime)
{
	// Move to aim location
	AimToTarget();
}

void ATankPlayerController::AimToTarget()
{
	// if getHitLocation
	// Tank-> MoveTowards 
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & outHitLocation)
{
	int32 ViewportSizeX, ViewportSizeY;
	// Get Screen Size
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(CrosshairXLocation * ViewportSizeX, CrosshairYLocation * ViewportSizeY);
	FVector WorldLocation;
	FVector WorldDirection;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection))
	{// ʹ��������ײ����
		return GetLookVectorHitLocation(WorldDirection, outHitLocation);
	}

	return false;
}

// Ѱ������ײ���ĵ�
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & OutHitLocation)
{
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + LookDirection * LineTraceRange;

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	
	OutHitLocation = FVector(0.0f);
	return false;
}

ATank* ATankPlayerController::GetControlledTank()
{

	return Cast<ATank>(GetPawn());
}