// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPCCourseGameMode.h"
#include "RPCCourseCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "RPCController.h"
#include <GameFramework/PlayerStart.h>
#include <Kismet/GameplayStatics.h>
#include "ExCommon.h"

ARPCCourseGameMode::ARPCCourseGameMode()
{
	PlayerControllerClass = ARPCController::StaticClass();

	// �������worldSetting ָ��gamemode����Ϸ����ʱ���Զ��Ѵ�����Ŀ����ʱ����Ŀ��GameMode ������������ȥ
	// ���������GameMode ��ָ��PawnClass�Ļ������Զ��趨ADefaultPawn�࣬ ������������������NULL
	DefaultPawnClass = NULL;
	PlayerCount = 0;
}

void ARPCCourseGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (NewPlayer->GetPawn())
	{
		GetWorld()->DestroyActor(NewPlayer->GetPawn());
	}

	TArray<AActor*> ActArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), ActArray);
	if (ActArray.Num() > 0)
	{
		PlayerCount++;
		UClass* CharacterClass = LoadClass<ARPCCourseCharacter>(NULL, TEXT("Blueprint'/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter.ThirdPersonCharacter_C'"));

		ARPCCourseCharacter* NewCharacter = GetWorld()->SpawnActor<ARPCCourseCharacter>(CharacterClass, ActArray[0]->GetActorLocation() + FVector(0.f, PlayerCount * 200.f, 0.f), ActArray[0]->GetActorRotation());
		NewPlayer->Possess(NewCharacter);

		DDH::Debug() << NewPlayer->GetName() << " Login " << DDH::Endl();

	}

}

void ARPCCourseGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	PlayerCount--;

	DDH::Debug() << Exiting->GetName() << " Logout " << DDH::Endl();


}
