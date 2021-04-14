// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExRenderActor.generated.h"

// �����ڳ�������ȾRenderTexture ������ʹ��
UCLASS()
class KBECOURSEPRO_API AExRenderActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExRenderActor();


	UFUNCTION(BlueprintImplementableEvent)
		void SwitchRoleMesh(uint8 RoleType);



};
