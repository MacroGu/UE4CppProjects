// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RPCCourseGameMode.generated.h"

UCLASS(minimalapi)
class ARPCCourseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARPCCourseGameMode();

	// �û�����
	virtual void PostLogin(APlayerController* NewPlayer) override;

	// �û��˳�
	virtual void Logout(AController* Exiting) override;

};



