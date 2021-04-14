// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BagWidget/ExBagBlock.h"
#include "Overlay.h"
#include "OverlaySlot.h"
#include "ExGoodItem.h"
#include "ExGoodDrag.h"
#include "Scripts/ExEventData.h"
#include "Engine/KBEngine.h"


void UExBagBlock::UpdateBlock()
{
	// ��ExDataMgr ��ȡ�ø��Ӷ�Ӧ����Ʒ��Ϣ
	if (!UExDataMgr::Get()->IsGoodExist(BagType, BlockId))
	{
		if (GoodItem)
		{
			GoodItem->RemoveFromParent();
			GoodItem = NULL;
		}
	}
	else
	{
		const FGoodInfo GoodInfo = UExDataMgr::Get()->GetGoodInfo(BagType, BlockId);
		// ���GoodItem ������
		if (!GoodItem)
		{
			GoodItem = CreateWidget<UExGoodItem>(this, GoodItemClass);
			UOverlaySlot* ItemSlot = RootBox->AddChildToOverlay(GoodItem);
			ItemSlot->SetHorizontalAlignment(HAlign_Center);
			ItemSlot->SetVerticalAlignment(VAlign_Center);

			// ��ί��
			GoodItem->LeaveBagBlockDel.BindLambda([this]() {
				GoodItem = NULL;
				});

		}
		//  ������ݸ�GoodItem
		GoodItem->InitGoodItem(BagType, BlockId);
	}
}

void UExBagBlock::InitBlockInfo(EBagType InType, uint8 InId)
{
	BagType = InType;
	BlockId = InId;
}

void UExBagBlock::IsAllowDropDown(bool& DropResult)
{
	DropResult = false;

	// �жϿ����Ƿ�����Ʒ
	if (GoodItem)
	{
		return;
	}

	// �Ƿ���ԭ����
	if (UExDataMgr::Get()->HandBagType == BagType && UExDataMgr::Get()->HandBlockId == BlockId)
	{
		return;
	}

	const FGoodInfo HandGoodInfo = UExDataMgr::Get()->GetHandGoodInfo();

	// �ж��Ƿ�ƥ��
	switch (BagType)
	{
	case EBagType::MainBag:
		DropResult = true;
		break;
	case EBagType::SkillBag:
		if (HandGoodInfo.GoodType == EGoodType::Skill)
		{
			DropResult = true;
		}
		break;
	case EBagType::BuffBag:
		if (HandGoodInfo.GoodType == EGoodType::Buff)
		{
			DropResult = true;
		}
		break;
	case EBagType::EquipBag:
		if (HandGoodInfo.GoodType == EGoodType::Equip)
		{
			// װ����Ҫ�жϸ���ID
			if (HandGoodInfo.GoodKind == BlockId)
			{
				DropResult = true;
			}
		}
		break;
	default:
		break;
	}
}

void UExBagBlock::RequestPassGood()
{
	// ������������ƶ���Ʒ
	UKBEventData_PassGood* EventData = NewObject<UKBEventData_PassGood>();
	EventData->ArcBagType = (uint8)UExDataMgr::Get()->HandBagType;
	EventData->ArcBlockId = UExDataMgr::Get()->HandBlockId;
	EventData->DesBagType = (uint8)BagType;
	EventData->DesBlockId = BlockId;
	KBENGINE_EVENT_FIRE("PassGood", EventData);

	// �����ק����Ʒ��Ϣ
	if (UExDataMgr::Get()->GoodDrag)
	{
		UExDataMgr::Get()->GoodDrag->RemoveFromParent();
	}
	UExDataMgr::Get()->GoodDrag = NULL;

	// �����յ���Ʒ��Ϣ�Ϳյĸ�������, ���Ƴ���Ʒ����ʹ��
	FGoodInfo ArcGoodInfo;
	ArcGoodInfo.InitInfo(UExDataMgr::Get()->HandBlockId, 0, 0);

	// ��ǰ���Ӹ��µ���Ʒ����Ϣ
	FGoodInfo DesGoodInfo = UExDataMgr::Get()->GetHandGoodInfo();
	// �޸ĸ���id
	DesGoodInfo.BlockId = BlockId;

	// ������������
	UExDataMgr::Get()->ChangeGoodInfo(UExDataMgr::Get()->HandBagType, ArcGoodInfo);
	UExDataMgr::Get()->ChangeGoodInfo(BagType, DesGoodInfo);
}

void UExBagBlock::ReviseDragGood()
{
	UExDataMgr::Get()->ReviseHandGood();
}
