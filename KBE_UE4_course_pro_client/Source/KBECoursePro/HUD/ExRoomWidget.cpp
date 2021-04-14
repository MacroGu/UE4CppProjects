// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ExRoomWidget.h"
#include "Scripts/ExEventData.h"
#include "Engine/KBEngine.h"
#include "TextBlock.h"
#include "ExRoomItem.h"
#include "ScrollBox.h"
#include "ScrollBoxSlot.h"
#include "Scripts/ExCommon.h"
#include "WidgetTree.h"
#include "EditableTextBox.h"
#include "Center/ExRoomGameMode.h"
#include <Kismet/GameplayStatics.h>
#include "Center/ExGameInstance.h"



void UExRoomWidget::OnReqRoomList(TArray<FROOM_INFO> RoomList)
{
	// �Ѿɵ��б��Ƴ�
	for (int i = 0; i < RoomItemGroup.Num(); ++i)
	{
		RoomItemGroup[i]->RemoveFromParent();
		RoomItemGroup[i]->ConditionalBeginDestroy();
	}
	// �������
	RoomItemGroup.Empty();

	// ѭ������ RoomItem
	for (int i = 0; i < RoomList.Num(); ++i)
	{
		// ����RoomItem
		UExRoomItem* RoomItem = WidgetTree->ConstructWidget<UExRoomItem>(RoomItemClass);
		UScrollBoxSlot* RoomItemSlot = Cast<UScrollBoxSlot>(RoomListScroll->AddChild(RoomItem));
		RoomItemSlot->SetPadding(FMargin(0.f, 5.f, 0.f, 5.f));

		// ���÷�����Ϣ
		RoomItem->InitItem(RoomList[i]);
		RoomItem->RoomItemSelectDel.BindUObject(this, &UExRoomWidget::RoomItemSelect);

		// ���淿����Ŀ����������
		RoomItemGroup.Add(RoomItem);
	}

	// ���ֻ��һ�����䣬 ֱ��ѡ�и÷���
	if (RoomItemGroup.Num() == 1)
	{
		RoomItemSelect(RoomItemGroup[0]->RoomInfo.RoomId);
	}
}

void UExRoomWidget::OnCreateRoom(FROOM_INFO RoomInfo)
{

	// ����RoomItem
	UExRoomItem* RoomItem = WidgetTree->ConstructWidget<UExRoomItem>(RoomItemClass);
	UScrollBoxSlot* RoomItemSlot = Cast<UScrollBoxSlot>(RoomListScroll->AddChild(RoomItem));
	RoomItemSlot->SetPadding(FMargin(0.f, 5.f, 0.f, 5.f));

	// ���÷�����Ϣ
	RoomItem->InitItem(RoomInfo);
	RoomItem->RoomItemSelectDel.BindUObject(this, &UExRoomWidget::RoomItemSelect);

	// ���淿����Ŀ����������
	RoomItemGroup.Add(RoomItem);

	// ���ֻ��һ�����䣬 ֱ��ѡ�и÷���
	if (RoomItemGroup.Num() == 1)
	{
		RoomItemSelect(RoomItemGroup[0]->RoomInfo.RoomId);
	}

}

void UExRoomWidget::RefreshEvent()
{
	KBENGINE_EVENT_FIRE("ReqRoomList", NewObject<UKBEventData>());
}

void UExRoomWidget::CreateRoomEvent()
{
	// ��ȡ��������
	FString RoomName = RoomNameTextBox->GetText().ToString();

	RoomNameTextBox->SetText(FText());

	if (RoomName.IsEmpty())
	{
		DDH::Debug() << "Please Enter Room Name" << DDH::Endl();
		return;
	}

	UKBEventData_ReqCreateRoom* EventData = NewObject<UKBEventData_ReqCreateRoom>();
	EventData->RoomName = RoomName;

	KBENGINE_EVENT_FIRE("ReqCreateRoom", EventData);

}

void UExRoomWidget::EnterGameEvent()
{
	for (int i = 0; i < RoomItemGroup.Num(); ++i)
	{
		if (RoomItemGroup[i]->IsSelected)
		{
			// ����ѡ�еķ������ֵ� GameInstance
			UExGameInstance* GameInstance = Cast<UExGameInstance>(UGameplayStatics::GetGameInstance(RoomGameMode->GetWorld()));
			GameInstance->RoomName = FText::FromString(RoomItemGroup[i]->RoomInfo.Name);

			UKBEventData_SelectRoomGame* EventData = NewObject<UKBEventData_SelectRoomGame>();
			EventData->RoomId = RoomItemGroup[i]->RoomInfo.RoomId;
			KBENGINE_EVENT_FIRE("SelectRoomGame", EventData);
			return;
		}
	}

	DDH::Debug() << "Please Select Room" << DDH::Endl();

}

void UExRoomWidget::RoomItemSelect(uint64 RoomId)
{
	// ȡ��������ɫ��ѡ��
	for (int i = 0; i < RoomItemGroup.Num(); ++i)
	{
		if (RoomItemGroup[i]->RoomInfo.RoomId != RoomId)
		{
			RoomItemGroup[i]->UnItemSelect();
		}
		else
		{
			RoomItemGroup[i]->ItemSelect();
		}
	}
}
