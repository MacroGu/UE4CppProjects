// Fill out your copyright notice in the Description page of Project Settings.


#include "Center/ExRoleGameMode.h"
#include "Scripts/ExEventData.h"
#include "Scripts/ExCommon.h"
#include "Engine/KBEngine.h"
#include "HUD/ExRoleWidget.h"
#include "Scene/ExRenderActor.h"
#include "EngineUtils.h"
#include <Kismet/GameplayStatics.h>
#include "TextBlock.h"



void AExRoleGameMode::InstallEvent()
{

	Super::InstallEvent();

	KBENGINE_REGISTER_EVENT("OnReqRoleList", OnReqRoleList);
	KBENGINE_REGISTER_EVENT("OnCreateRole", OnCreateRole);
	KBENGINE_REGISTER_EVENT("OnRemoveRole", OnRemoveRole);
	KBENGINE_REGISTER_EVENT("OnSelectRoleGame", OnSelectRoleGame);

}

void AExRoleGameMode::BeginPlay()
{
	// ���ɽ����Լ���ȡ��ȾActor
	for (TActorIterator<AExRenderActor> ActorIt(GetWorld()); ActorIt; ++ActorIt)
	{
		RenderActor = Cast<AExRenderActor>(*ActorIt);
	}
	
	RoleWidget = CreateWidget<UExRoleWidget>(GetWorld(), RoleWidgetClass);
	RoleWidget->AddToViewport();
	RoleWidget->RoleGameMode = this;

	Super::BeginPlay();

}

void AExRoleGameMode::OnReqRoleList(const UKBEventData* EventData)
{
	const UKBEventData_OnReqRoleList* ServerData = Cast<UKBEventData_OnReqRoleList>(EventData);
	// ���߽�ɫ�����ɫ�б������ɽ�ɫ��
	RoleWidget->OnReqRoleList(ServerData->RoleList);

}

void AExRoleGameMode::OnCreateRole(const UKBEventData* EventData)
{
	const UKBEventData_OnCreateRole* ServerData = Cast<UKBEventData_OnCreateRole>(EventData);
	// ��� errorcode ��Ϊ 0 �� ˵���������ɹ�
	if (ServerData->ErrorCode == 0)
	{
		RoleWidget->OnCreateRole(ServerData->RoleInfo);
	}
}

void AExRoleGameMode::OnRemoveRole(const UKBEventData* EventData)
{
	const UKBEventData_OnRemoveRole* ServerData = Cast<UKBEventData_OnRemoveRole>(EventData);

	RoleWidget->OnRemoveRole(ServerData->RoleInfo);
}

void AExRoleGameMode::OnSelectRoleGame(const UKBEventData* EventData)
{
	const UKBEventData_OnSelectRoleGame* ServerData = Cast<UKBEventData_OnSelectRoleGame>(EventData);

	// ֱ����תѡ�񷿼䳡��
	UGameplayStatics::OpenLevel(GetWorld(), FName("RoomMap"));

}
