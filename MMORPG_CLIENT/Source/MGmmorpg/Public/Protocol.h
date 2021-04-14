/*
	author: Macro Gu
	email: macrogu@qq.com
	QQ: 877188891

	��ϢЭ���ID
*/

#pragma once



// ��Ϣ���Ͷ���   ��¼����   21000 ~ 21999
enum EPacketTypeLogin
{
	REGISTER_ACCOUNT_REQ = 21000,		// ����ע��
	REGISTER_ACCOUNT_RPO = 21001,		// ע�᷵��
	LOGIN_SERVER_REQ = 21002,			// �����¼
	LOGIN_SERVER_RPO = 21003,			// ��¼����
	KEY_LOGIN_SERVER_REQ = 20024,		// ����ͨ��key��¼
	KEY_LOGIN_SERVER_RPO = 20025,		// ͨ��key��¼����
};

// ��Ϣ���Ͷ���   ����״̬ 22000 ~ 22999
enum EPacketTypeScene
{
	ENROLL_ENTER_SCENE_REQ = 22000,		// ���볡�� ����
	ENROLL_ENTER_SCENE_RPO = 22001,		// ���볡�� ����
	PLAYER_MOVEMENT_REQ = 22002,		// ͬ���������״̬ ����
	PLAYER_MOVEMENT_RPO = 22003,		// ͬ���������״̬ ����
	LEAVE_SCENE_REQ = 22004,			// �뿪���� ����
	LEAVE_SCENE_RPO = 22005,			// �뿪���� ����
	BROCAST_NEW_PLAYER = 22006,			// �㲥 ����ҽ��볡��
	BROCAST_PLAYER_LEAVE = 22007,		// �㲥 ����뿪����
	PLAYER_HIT_MONSTER_REQ = 22008,		// ������󹥻����� ����
	PLAYER_HIT_MONSTER_RPO = 22009,		// ������󹥻����� ����
	BROCAST_PLAYER_HIT_MONSTER = 22010,		// �㲥 ��ҹ�������
	BROCAST_PLAYER_MOVEMENT = 22011,		// �㲥 ����ڳ����ڵ��ƶ�

};


// ��Ϣ���Ͷ���  ��Ҳ��������Ϣ 23000 ~ 23999
enum EPacketTypeEntity
{
	NOTIFY_SELF_PROP_CHANGE = 23000,			// ֪ͨ�Լ����Ա仯
	BROCAST_OTHER_PROP_CHANGE = 23001,			// �㲥��֪����ʵ�����Ա仯
	BROCAST_ALL_ENTITIES_PROPS = 23002,			// �㲥ȫ�����ʵ�������

};

