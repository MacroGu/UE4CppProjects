// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BagWidget/ExGoodItem.h"
#include "Image.h"
#include "TextBlock.h"


void UExGoodItem::InitGoodItem(EBagType InType, uint8 InId)
{
	BagType = InType;
	BlockId = InId;

	// ����UI
	const FGoodInfo GoodInfo = UExDataMgr::Get()->GetGoodInfo(BagType, BlockId);
	NumberText->SetText(FText::FromString(FString::FromInt(GoodInfo.Number)));
	GoodImage->SetBrushFromTexture((UTexture2D*)UExDataMgr::Get()->GetGoodTexture(GoodInfo.GoodId));

}

void UExGoodItem::IsAllowDragUp(bool& IsAllow)
{
	// �жϵ�ǰ�Ƿ�����Ʒ����ק
	if (UExDataMgr::Get()->IsHandGoodExist())
	{
		IsAllow = false;
		return;
	}

	IsAllow = true;
}

void UExGoodItem::AcceptDragUp(uint8& GoodId, uint8& Number)
{
	// ��ȡ��Ʒ��Ϣ
	const FGoodInfo GoodInfo = UExDataMgr::Get()->GetGoodInfo(BagType, BlockId);

	// ������ק��Ϣ��������
	UExDataMgr::Get()->HandBagType = BagType;
	UExDataMgr::Get()->HandBlockId = BlockId;

	// �������ݸ���ͼ
	GoodId = GoodInfo.GoodId;
	Number = GoodInfo.Number;

}

void UExGoodItem::LeaveBagBlock()
{
	// ����ί�и������������Լ����Ƴ�
	LeaveBagBlockDel.ExecuteIfBound();
	RemoveFromParent();
}
