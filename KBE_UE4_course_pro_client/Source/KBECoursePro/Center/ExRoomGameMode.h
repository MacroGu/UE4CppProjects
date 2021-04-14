// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Center/ExKbeGameMode.h"
#include "ExRoomGameMode.generated.h"


class UExRoomWidget;
class UKBEventData;

/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API AExRoomGameMode : public AExKbeGameMode
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere)
		TSubclassOf<UExRoomWidget> RoomWidgetClass;

	UExRoomWidget* RoomWidget;

public:

	// ���󷿼��б�ص�����
	void OnReqRoomList(const UKBEventData* EventData);

	// �������ۻص�����
	void OnCreateRoom(const UKBEventData* EventData);

	// ��ҽ�����Ϸ����
	void AddSpaceGeometryMapping(const UKBEventData* EventData);

protected:

	virtual void BeginPlay() override;

	virtual void InstallEvent() override;

	
};
