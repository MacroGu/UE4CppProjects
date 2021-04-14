// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ExMmoWidget.h"
#include "TextBlock.h"
#include "ProgressBar.h"
#include "Overlay.h"
#include "Engine/KBEngine.h"
#include "Scripts/ExEventData.h"
#include "BagWidget/ExEquipBag.h"
#include "BagWidget/ExMainBag.h"
#include "BagWidget/ExBuffBag.h"
#include "BagWidget/ExSkillBag.h"
#include "Player/ExPlayerCharacter.h"
#include <Scripts/ExCommon.h>
#include "ExChatRoom.h"




void UExMmoWidget::InstallEvents(FText RoomName)
{
	// ���÷�������
	RoomText->SetText(RoomName);

	// �󶨱�������ί��
	UExDataMgr::Get()->UpdateBagBlockDel.BindUObject(this, &UExMmoWidget::UpdateBagBlock);

	// ��ע���¼�
	KBENGINE_REGISTER_EVENT("OnReqBagList", OnReqBagList);
	KBENGINE_REGISTER_EVENT("OnPassGood", OnPassGood);
	KBENGINE_REGISTER_EVENT("OnReduceGood", OnReduceGood);
	KBENGINE_REGISTER_EVENT("OnIncreaseGood", OnIncreaseGood);

	ChatRoom->InstallEvent();

}

void UExMmoWidget::UnInstallEvents()
{
	// ע���ö���󶨵�����KBE�¼�
	KBENGINE_DEREGISTER_ALL_EVENT();

	// ����������ע��KBE�¼�
	ChatRoom->UnInstallEvents();

}

void UExMmoWidget::SetName(FString InName)
{
	NameText->SetText(FText::FromString(InName));
}

void UExMmoWidget::SetHpPercent(float InPercent)
{
	BloodProgress->SetPercent(InPercent);
	BloodProgress->SetFillColorAndOpacity(FLinearColor(1.f - InPercent, InPercent, 0.f));

	// ��� HP Ϊ0�� ��ʾ����UI
	if (InPercent == 0.f)
	{
		if (ReliveBox->GetVisibility() == ESlateVisibility::Hidden)
		{
			ReliveBox->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		if (ReliveBox->GetVisibility() == ESlateVisibility::Visible)
		{
			ReliveBox->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UExMmoWidget::ReliveEvent()
{
	KBENGINE_EVENT_FIRE("Relive", NewObject<UKBEventData>());
}

void UExMmoWidget::LeaveRoom()
{
	// �뿪���䣬 ����ѡ���ɫ����
	KBENGINE_EVENT_FIRE("LeaveRoom", NewObject<UKBEventData>());
}

void UExMmoWidget::OpenOrCloseBag(bool IsOpen)
{
	if (IsOpen)
	{
		MainBag->SetVisibility(ESlateVisibility::Visible);
		EquipBag->SetVisibility(ESlateVisibility::Visible);
		ChatRoom->ShowOrHideInput(true);
	}
	else
	{
		MainBag->SetVisibility(ESlateVisibility::Hidden);
		EquipBag->SetVisibility(ESlateVisibility::Hidden);
		ChatRoom->ShowOrHideInput(false);
	}
}

void UExMmoWidget::ReviseDragGood()
{
	UExDataMgr::Get()->ReviseHandGood();
}

void UExMmoWidget::SetBaseHp(int32 InBaseHp)
{
	EquipBag->SetBaseHp(InBaseHp);
}

void UExMmoWidget::SetDefense(int32 InDefense)
{
	EquipBag->SetDefense(InDefense);
}

void UExMmoWidget::SetPowerRatio(float InPowerRatio)
{
	EquipBag->SetPowerRatio(InPowerRatio);
}

void UExMmoWidget::SetSpeedRatio(float InSpeedRatio)
{
	EquipBag->SetSpeedRatio(InSpeedRatio);
}

void UExMmoWidget::UpdateSkillOn()
{
	SkillBag->UpdateSkillOn();
}

void UExMmoWidget::OnReqBagList(const UKBEventData* EventData)
{
	const UKBEventData_OnReqBagList* ServerData = Cast<UKBEventData_OnReqBagList>(EventData);

	for (auto Info : ServerData->MainBag)
	{
		FGoodInfo GoodInfo;
		GoodInfo.InitInfo(Info.BlockId, Info.GoodId, Info.Number);
		UExDataMgr::Get()->ChangeGoodInfo(EBagType::MainBag, GoodInfo);
	}

	for (auto Info : ServerData->SkillBag)
	{
		FGoodInfo GoodInfo;
		GoodInfo.InitInfo(Info.BlockId, Info.GoodId, Info.Number);
		UExDataMgr::Get()->ChangeGoodInfo(EBagType::SkillBag, GoodInfo);
	}

	for (auto Info : ServerData->BuffBag)
	{
		FGoodInfo GoodInfo;
		GoodInfo.InitInfo(Info.BlockId, Info.GoodId, Info.Number);
		UExDataMgr::Get()->ChangeGoodInfo(EBagType::BuffBag, GoodInfo);
	}

	for (auto Info : ServerData->EquipBag)
	{
		FGoodInfo GoodInfo;
		GoodInfo.InitInfo(Info.BlockId, Info.GoodId, Info.Number);
		UExDataMgr::Get()->ChangeGoodInfo(EBagType::EquipBag, GoodInfo);
	}
}

void UExMmoWidget::UpdateBagBlock(EBagType BagType, uint8 BlockId)
{
	switch (BagType)
	{
	case EBagType::MainBag:
		MainBag->UpdateBlock(BlockId);
		break;
	case EBagType::SkillBag:
		SkillBag->UpdateBlock(BlockId);
		break;
	case EBagType::BuffBag:
		BuffBag->UpdateBlock(BlockId);
		break;
	case EBagType::EquipBag:
		EquipBag->UpdateBlock(BlockId);
		break;
	default:
		break;
	}
}

void UExMmoWidget::OnPassGood(const UKBEventData* EventData)
{
	const UKBEventData_OnPassGood* ServerData = Cast<UKBEventData_OnPassGood>(EventData);
	EBagType ArcBagType = (EBagType)ServerData->ArcBagType;
	FGoodInfo ArcGoodInfo;
	ArcGoodInfo.InitInfo(ServerData->ArcGoodInfo.BlockId, ServerData->ArcGoodInfo.GoodId, ServerData->ArcGoodInfo.Number);

	EBagType DesBagType = (EBagType)ServerData->DesBagType;
	FGoodInfo DesGoodInfo;
	DesGoodInfo.InitInfo(ServerData->DesGoodInfo.BlockId, ServerData->DesGoodInfo.GoodId, ServerData->DesGoodInfo.Number);

	// ֱ�Ӹ���DataMgr�ı�������
	UExDataMgr::Get()->ChangeGoodInfo(ArcBagType, ArcGoodInfo);
	UExDataMgr::Get()->ChangeGoodInfo(DesBagType, DesGoodInfo);

}

void UExMmoWidget::OnReduceGood(const UKBEventData* EventData)
{
	const UKBEventData_OnReduceGood* ServerData = Cast<UKBEventData_OnReduceGood>(EventData);

	// ��ȡ����
	EBagType BagType = (EBagType)ServerData->BagType;
	FGoodInfo GoodInfo;
	GoodInfo.InitInfo(ServerData->GoodInfo.BlockId, ServerData->GoodInfo.GoodId, ServerData->GoodInfo.Number);

	if (ServerData->ReduceRes == 1)
	{
		// ���ʹ�óɹ������ּ��ܺ�buff����Ч��
		if (GoodInfo.GoodType == EGoodType::Skill)
		{
			// ����Character������������й���
			if (PlayerCharacter)
			{
				PlayerCharacter->Attack(GoodInfo.GoodKind);
			}
		}
		else
		{
			// buff, ����������Ч
		}
	}

	// ����ʹ���Ƿ�ɹ���Ҫ���±�����Ʒ
	// �ȸ�������
	UExDataMgr::Get()->ChangeGoodInfo(BagType, GoodInfo);
}

void UExMmoWidget::OnIncreaseGood(const UKBEventData* EventData)
{
	const UKBEventData_OnIncreaseGood* ServerData = Cast<UKBEventData_OnIncreaseGood>(EventData);

	EBagType BagType = (EBagType)ServerData->BagType;
	FGoodInfo GoodInfo;
	GoodInfo.InitInfo(ServerData->GoodInfo.BlockId, ServerData->GoodInfo.GoodId, ServerData->GoodInfo.Number);

	// ������Ʒ�����ڴ�������ƷΪ�յ����⣬ ����ֱ�����ӱ�����Ʒ
	UExDataMgr::Get()->ChangeGoodInfo(BagType, GoodInfo);


}
