// Fill out your copyright notice in the Description page of Project Settings.


#include "Center/ExLoginGameMode.h"
#include "Engine/KBEngine.h"
#include "Scripts/ExCommon.h"
#include "Engine/KBEvent.h"
#include "Engine/KBEMain.h"
#include "HUD/ExLoginWidget.h"
#include "ExKBEClient.h"



void AExLoginGameMode::InstallEvent()
{
	Super::InstallEvent();

	//�����û����ʵ��ص�
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onCreateAccountResult, OnCreateAccountResult);
	//��½ʧ�ܻص�
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginFailed, OnLoginFailed);
	//�汾ƥ��ص�
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onVersionNotMatch, OnVersionNotMatch);
	//�汾��ƥ��ص�
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onScriptVersionNotMatch, OnScriptVersionNotMatch);
	//��½baseappʧ�ܻص�
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginBaseappFailed, OnLoginBaseappFailed);
	//��½baseapp�ص�
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginBaseapp, OnLoginBaseapp);
	//��½�ɹ��ص�, ����ExAccount����__init__()ʱ����, ��������ת��ѡ���ɫ����
	KBENGINE_REGISTER_EVENT("onLoginSuccessfully", OnLoginSuccessfully);

}

void AExLoginGameMode::BeginPlay()
{
	// ÿ�ν��뵽��¼����ʱ������һ��KBE�� ����KBE�����������һֱ����
	KBEngine::KBEngineApp::getSingleton().reset();

	Super::BeginPlay();

	LoginWidget = CreateWidget<UExLoginWidget>(GetWorld(), LoginWidgetClass);
	LoginWidget->AddToViewport();
	LoginWidget->LoginGameMode = this;
	LoginWidget->InitWidget();


	for (TActorIterator<AExKBEClient> ActorIt(GetWorld()); ActorIt; ++ActorIt)
	{
		KBEMain = (*ActorIt)->KBEMain;
	}

}

void AExLoginGameMode::OnCreateAccountResult(const UKBEventData* pEventData)
{

	const UKBEventData_onCreateAccountResult* ServerData = Cast<UKBEventData_onCreateAccountResult>(pEventData);
	DDH::Debug() << "OnCreateAccountResult, errorCode: " << ServerData->errorCode << " errorStr: " << ServerData->errorStr << DDH::Endl();

}

void AExLoginGameMode::OnLoginFailed(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginFailed* ServerData = Cast<UKBEventData_onLoginFailed>(pEventData);
	DDH::Debug() << "OnLoginFailed, failedcode: " << ServerData->failedcode << " errorStr: " << ServerData->errorStr << DDH::Endl();
}

void AExLoginGameMode::OnVersionNotMatch(const UKBEventData* pEventData)
{
	const UKBEventData_onVersionNotMatch* ServerData = Cast<UKBEventData_onVersionNotMatch>(pEventData);
	DDH::Debug() << "OnVersionNotMatch, clientVersion: " << ServerData->clientVersion << " serverVersion: " << ServerData->serverVersion << DDH::Endl();
}

void AExLoginGameMode::OnScriptVersionNotMatch(const UKBEventData* pEventData)
{
	const UKBEventData_onScriptVersionNotMatch* ServerData = Cast<UKBEventData_onScriptVersionNotMatch>(pEventData);
	DDH::Debug() << "OnScriptVersionNotMatch, clientScriptVersion: " << ServerData->clientScriptVersion << " serverScriptVersion: " << ServerData->serverScriptVersion << DDH::Endl();

}

void AExLoginGameMode::OnLoginBaseappFailed(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginBaseappFailed* ServerData = Cast<UKBEventData_onLoginBaseappFailed>(pEventData);
	DDH::Debug() << "OnLoginBaseappFailed, failedcode: " << ServerData->failedcode << " errorStr: " << ServerData->errorStr << DDH::Endl();
}

void AExLoginGameMode::OnLoginBaseapp(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginBaseapp* ServerData = Cast<UKBEventData_onLoginBaseapp>(pEventData);
	DDH::Debug() << "OnLoginBaseapp, eventName: " << ServerData->eventName << DDH::Endl();
}

void AExLoginGameMode::OnLoginSuccessfully(const UKBEventData* pEventData)
{
	const UKBEventData_onLoginSuccessfully* ServerData = Cast<UKBEventData_onLoginSuccessfully>(pEventData);
	DDH::Debug() << "OnLoginBaseappFailed, entity_uuid: " << ServerData->entity_uuid << " entity_id: " << ServerData->entity_id << DDH::Endl();

	UGameplayStatics::OpenLevel(GetWorld(), FName("RoleMap"));

}
