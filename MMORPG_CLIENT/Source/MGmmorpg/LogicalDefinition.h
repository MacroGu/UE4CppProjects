/*
	author: Macro Gu
	email: macrogu@qq.com
	QQ: 877188891

	��Ϸ�߼���Ҫ�õ�һЩ����
*/

#pragma once
#include <stdint.h>


#define UE4_LOCATION_TO_SERVER 100


// �����Ҫͬ����״̬   
struct stPlayerStatus
{
	// �ỰID�� ΨһID
	int64_t		SessionId;
	int64_t		uid;	//��ɫΨһuid

	// λ��
	float	PositionX;
	float	PositionY;
	float	PositionZ;
	// ��תֵ
	float	Pitch;
	float	Yaw;
	float	Roll;
	// �ٶ�
	float SpeedX;
	float SpeedY;
	float SpeedZ;
	// �Ƿ����
	bool	IsAlive;
	// Ѫ��
	float	HealthValue;
	// �Ƿ��ڹ���
	bool	IsAttacking;

	stPlayerStatus()
	{
		ClearStatus();
	}

	~stPlayerStatus()
	{

	}

	void ClearStatus()
	{
		SessionId = 0;
		PositionX = 0.f;
		PositionY = 0.f;
		PositionZ = 0.f;
		Yaw = 0.f;
		Pitch = 0.f;
		Roll = 0.f;
		SpeedX = 0.f;
		SpeedY = 0.f;
		SpeedZ = 0.f;
		IsAlive = false;
		HealthValue = 0.f;
		IsAttacking = false;
	}

	stPlayerStatus& operator = (const stPlayerStatus& newStatus)
	{
		if (this != &newStatus)
		{
			SessionId = newStatus.SessionId;
			PositionX = newStatus.PositionX;
			PositionY = newStatus.PositionY;
			PositionZ = newStatus.PositionZ;
			Yaw = newStatus.Yaw;
			Pitch = newStatus.Pitch;
			Roll = newStatus.Roll;
			SpeedX = newStatus.SpeedX;
			SpeedY = newStatus.SpeedY;
			SpeedZ = newStatus.SpeedZ;
			IsAlive = newStatus.IsAlive;
			HealthValue = newStatus.HealthValue;
			IsAttacking = newStatus.IsAttacking;
		}

		return *this;
	}

};


// �����״̬
struct stMonsterStatus
{
	// uuid�� ΨһID
	int64_t		uuid;

	// λ��
	float	PositionX;
	float	PositionY;
	float	PositionZ;

	// �Ƿ����
	bool	IsAlive;
	// Ѫ��
	float	HealthValue;
	// �Ƿ��ڹ���
	bool	IsAttacking;
	// ��Ұ��Χ
	float	TraceRange;
	// ������Χ
	float	HitRange;
	// ÿ���ƶ���Ԫ��
	float	MovePoint;
	// ÿ�ι�����Ԫ��
	float	HitPoint;
	// �Ƿ���׷Ѱ���
	bool IsTracking;

	stMonsterStatus()
	{
		ClearStatus();
	}

	~stMonsterStatus()
	{

	}

	void ClearStatus()
	{
		uuid = 0;
		PositionX = 0.f;
		PositionY = 0.f;
		PositionZ = 0.f;
		IsAlive = false;
		HealthValue = 0.f;
		IsAttacking = false;
		TraceRange = 0.f;
		HitRange = 0.f;
		MovePoint = 0.f;
		HitPoint = 0.f;
		IsTracking = false;

	}

	stMonsterStatus& operator = (const stMonsterStatus& newStatus)
	{
		if (this != &newStatus)
		{
			uuid = newStatus.uuid;
			PositionX = newStatus.PositionX;
			PositionY = newStatus.PositionY;
			PositionZ = newStatus.PositionZ;
			IsAlive = newStatus.IsAlive;
			HealthValue = newStatus.HealthValue;
			IsAttacking = newStatus.IsAttacking;
			TraceRange = newStatus.TraceRange;
			HitRange = newStatus.HitRange;
			MovePoint = newStatus.MovePoint;
			HitPoint = newStatus.HitPoint;
			IsTracking = newStatus.IsTracking;
		}

		return *this;
	}

};

// ������ entity ������
enum EntityType
{
	ENTITY_TYPE_INVALID = 0,
	ENTITY_TYPE_PLAYER = 1,		//����
	ENTITY_TYPE_MONSTER = 2,	//����

};


// ʵ�������
enum EntityProp
{
	ENTITY_PROP_BEGIN = 0,	// ��ʼ
	ENTITY_PROP_HP = 3,		//��ǰѪ��ֵ
	ENTITY_ATTACK_VALUE = 4,		// ������


	ENTITY_PROP_END = 9999,
};
