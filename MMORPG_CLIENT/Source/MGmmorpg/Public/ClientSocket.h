// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Core/Public/HAL/Runnable.h"
#include "Runtime/Sockets/Public/Sockets.h"
#include "GameFramework/GameModeBase.h"
#include <google/protobuf/message.h>
#include "Proto/login.pb.h"
#include "Proto/scene.pb.h"
#include "Proto/entity.pb.h"
#include "LogicalDefinition.h"
#include "Protocol.h"


#define	MAX_BUFFER		4096

class AMGPlayerController;
class APlayerCharacter;

/**
 * 
 */
class MGMMORPG_API ClientSocket
{
public:
	ClientSocket();
	virtual ~ClientSocket();

	// ��ʼ�� socket
	bool InitSocket();
	// ���ӷ�����
	bool ConnectServer();
	// ���÷�������IP ��port
	void SetServerIPandPort(const FString& serverIP, const int32& serverPort);

	// ע��
	bool SignUp(const FText& Account, const FText& Pw);
	bool SignUpRsp(char* data, int len);
	// ��¼
	bool Login(const FText& Account, const FText& Pw);
	bool LoginRsp(char* data, int len);
	// ������볡��
	void EnterScene(APlayerCharacter* CurPlayer);
	// ������볡��  �ظ�
	void EnterSceneRsp(char* data, int len);
	//�յ�������ҽ��볡��
	void NewPlayerEnterScene(char* data, int len);	
	// ��������Լ���״̬   ����������״̬��������֣������ô˽ӿ�
	void MovementStatusChanged(APlayerCharacter* CurPlayer, const FVector& new_location);
	// �������״̬�ı� ������������
	void PlayerMovementRsp(char* data, int len);
	// ���յ��������㲥������ҵ�״̬  ͬ��������ҵ�״̬
	void OtherPlayerMovementBrocast(char* data, int len);
	// ���յ��������㲥�� ��ҹ�������
	void OtherPlayerHitMonster(char* data, int len);
	// ���������
	void HitMonster(APlayerCharacter* CurPlayer);
	// �������Ա仯
	void OtherEntityPropChanged(char* data, int len);
	// ͬ������ʵ������
	void SyncOtherEntitiesProps(char* data, int len);

	// �����Լ����ƶ����߽��볡���� ��Ҫ��ʼ��һЩ�µ�ʵ��
	void NotifyPlayerWhenEntityEnter(char* data, int len);
	// �����Լ����ƶ������뿪������ ��Ҫ����һЩ�µ�ʵ��
	void NotifyPlayerWhenEntityLeave(char* data, int len);

	// �� player character to proto status
	void FromPlayerCharacterToProtoStatus(APlayerCharacter* player, SceneMsg::Struct_Player_Status* protostatus);
	// �� stPlayerStatus �� proto status
	void FromPlayerStatusToProtoStatus(stPlayerStatus& playerstatus,const SceneMsg::Struct_Player_Status& protoPlayerStatus);
	// �� stMonsterStatus �� proto status
	void FromMonsterStatusToProtoStatus(stMonsterStatus& monsterstatus, const SceneMsg::Struct_Monster_Status& protoMonsterStatus);

	// �ַ���Ϣ
	void DistributeMsg(char* recvData, int32_t dataLen);

	// ���� playercontroller
	void SetPlayerController(AMGPlayerController* pPlayerController);
	// ���� login game mode
	void SetCurrentGameMode(AGameModeBase* GameMode);
	// �������� ͳһ�ӿ�
	bool SendDataToServer(const uint16_t& msgID, ::google::protobuf::Message& protobufData);
	// is login success
	bool IsLoginSuccess() { return isLoginSuccess; }

	int32_t GetSessionID() { return sessionID; }

	uint32 DealWithServerMsg();
	virtual bool Init();

	static ClientSocket* GetSingleton()
	{
		static ClientSocket ins;
		return &ins;
	}

private:
	FSocket* SocketClient;
	FString serverIP;
	int32 serverPort;
	int32 sessionID;		// �ͻ���Ψһ session ID
	bool isLoginSuccess;

	AMGPlayerController* PlayerController;	// player Controller ���
	AGameModeBase* CurrentGameMode;			// ��ǰ��gamemode

};
