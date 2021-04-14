// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <map>
#include <unordered_map>
#include "GameFramework/PlayerController.h"
#include "LogicalDefinition.h"
#include "MGPlayerController.generated.h"

class APlayerCharacter;

/**
 * 
 */
UCLASS()
class MGMMORPG_API AMGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMGPlayerController();
	~AMGPlayerController();

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class ACharacter> WhoToSpawn;
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class ACharacter> MonsterToSpawn;


	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// ���³����е����������   ������ҽ��볡����ʱ�� 
	void OtherPlayerEnterInsight(stPlayerStatus& newPlayerStatus);
	// �����������״̬   ������һ��
	bool UpdateOtherPlayerStatus(const stPlayerStatus& OtherPlayerStatus);
	// ���³����е������Ĺ���   ������ҽ��볡����ʱ�� 
	void UpdateOtherMonster(stMonsterStatus& newMonsterStatus);
	// �������������״̬
	bool UpdateWorldMonsterInfo(const std::map<int64_t, stPlayerStatus>& updatedInSightMonsters);
	// ������ҹ�������
	void OtherPlayerHitMonster(const int64_t& attackerUUID, const int64_t& monsterID);
	// ʵ�����Է����仯
	void OnEntityPropChanged(const int64_t& entityID, const int32_t& ID, const int32_t& Value);
	// ʵ�����Գ�ʼ��
	void OnEntityPropInitialize(const int64_t& entityID, const std::unordered_map<int32_t, int32_t>& allProps);
	// �Ƴ����ʵ��
	void RemovePlayerEntity(const int64_t iPlayerUUID);
	

	// �����µ����
	void GenerateNewPlayer();

	// ģ����ҵ��ƶ�
	void SimulatePlayerRun();

	APlayerCharacter* second_player;

private:

	std::map<int64_t, stPlayerStatus> InSightPlayers;	// ��Ұ��Χ�ڵ�ȫ�����
	std::map<int64_t, stMonsterStatus> InSightMonsters; // ��Ұ��Χ�ڵĹ���

	int					SessionId;

	bool bIsConnected;	// �Ƿ񱣳�����


	bool bIsChatNeedUpdate;

	int	nPlayers;

	int nMonsters;

	bool bIsNeedToSpawnMonster;

	bool bIsNeedToDestroyMonster;
};
