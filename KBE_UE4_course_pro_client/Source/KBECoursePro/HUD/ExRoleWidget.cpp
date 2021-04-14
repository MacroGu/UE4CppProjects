// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ExRoleWidget.h"
#include "EditableTextBox.h"
#include "CheckBox.h"
#include "TextBlock.h"
#include "Button.h"
#include "HorizontalBox.h"
#include "Scripts/ExCommon.h"
#include "Scripts/ExEventData.h"
#include "Engine/KBEngine.h"
#include "ExRoleItem.h"
#include "WidgetTree.h"
#include "ScrollBox.h"
#include "ScrollBoxSlot.h"
#include "Center/ExRoleGameMode.h"
#include "Scene/ExRenderActor.h"





void UExRoleWidget::OnReqRoleList(TArray<FROLE_INFO> RoleList)
{
	for (int i = 0; i < RoleList.Num(); ++i)
	{
		// ����RoleItem
		UExRoleItem* RoleItem = WidgetTree->ConstructWidget<UExRoleItem>(RoleItemClass);
		UScrollBoxSlot* RoleItemSlot = Cast<UScrollBoxSlot>(RoleItemScroll->AddChild(RoleItem));
		RoleItemSlot->SetPadding(FMargin(0.f, 5.f, 0.f, 5.f));

		// ���ý�ɫ��Ϣ
		RoleItem->InitItem(RoleList[i]);
		RoleItem->RoleItemSelectDel.BindUObject(this, &UExRoleWidget::RoleItemSelect);

		// �����ɫ��Ŀ����������
		RoleItemGroup.Add(RoleItem);

		if (RoleItem->RoleInfo.IsLastRole)
		{
			RoleItemSelect(RoleItem->RoleInfo.Dbid);
		}
	}
}

void UExRoleWidget::OnCreateRole(FROLE_INFO RoleInfo)
{
	// ���� RoleItem ������ӵ�����
	UExRoleItem* RoleItem = WidgetTree->ConstructWidget<UExRoleItem>(RoleItemClass);
	UScrollBoxSlot* RoleItemSlot = Cast<UScrollBoxSlot>(RoleItemScroll->AddChild(RoleItem));
	RoleItemSlot->SetPadding(FMargin(0.f, 5.f, 0.f, 5.f));

	// ���ý�ɫ��Ϣ
	RoleItem->InitItem(RoleInfo);
	RoleItem->RoleItemSelectDel.BindUObject(this, &UExRoleWidget::RoleItemSelect);

	// �����ɫ��Ŀ����������
	RoleItemGroup.Add(RoleItem);

	// �����ǰֻ��һ����ɫ, ��ѡ��ý�ɫ
	if (RoleItemGroup.Num() == 1)
	{
		RoleItemSelect(RoleInfo.Dbid);
	}

}

void UExRoleWidget::OnRemoveRole(FROLE_INFO RoleInfo)
{
	// ��ȡ�Ƴ��Ľ�ɫ
	UExRoleItem* RoleItem = NULL;
	for (int i = 0; i < RoleItemGroup.Num(); ++i)
	{
		if (RoleItemGroup[i]->RoleInfo.Dbid == RoleInfo.Dbid)
		{
			RoleItem = RoleItemGroup[i];
		}
	}
	// �����ɫ������
	if (!RoleItem)
	{
		DDH::Debug() << "UExRoleWidget::OnRemoveRole : No RoleInfo Exit By Dbid --> " << RoleInfo.Dbid << DDH::Endl();
		return;
	}

	// �Ƴ�RoleItem
	RoleItemScroll->RemoveChild(RoleItem);
	RoleItemGroup.Remove(RoleItem);

	// �����ɫ�б�Ϊ�գ�  ��ѡ���һ����ɫ
	if (RoleItemGroup.Num() > 0)
	{
		RoleItemSelect(RoleItemGroup[0]->RoleInfo.Dbid);
	}

}

void UExRoleWidget::EnterGameEvent()
{
	// ��ȡ��ǰѡ��Ľ�ɫ
	for (int i = 0; i < RoleItemGroup.Num(); ++i)
	{
		if (RoleItemGroup[i]->RoleInfo.IsLastRole)
		{
			UKBEventData_ReqSelectRoleGame* EventData = NewObject<UKBEventData_ReqSelectRoleGame>();
			EventData->RoleInfo = RoleItemGroup[i]->RoleInfo;
			KBENGINE_EVENT_FIRE("ReqSelectRoleGame", EventData);
			return;
		}
	}

	// ������е�����˵��û��ѡ���κν�ɫ
	DDH::Debug() << "UExRoleWidget::EnterGameEvent : No Role Selected" << DDH::Endl();

}

void UExRoleWidget::CreateRoleEvent()
{
	EnterGameButton->SetVisibility(ESlateVisibility::Hidden);
	RoleTypeBox->SetVisibility(ESlateVisibility::Visible);

	CreateRoleButton->SetVisibility(ESlateVisibility::Hidden);
	RoleNameTextBox->SetVisibility(ESlateVisibility::Visible);

	RemoveRoleButton->SetVisibility(ESlateVisibility::Hidden);
	SureButton->SetVisibility(ESlateVisibility::Visible);
	CancelButton->SetVisibility(ESlateVisibility::Visible);

}

void UExRoleWidget::RemoveRoleEvent()
{
	// ��ȡ��ǰѡ��Ľ�ɫ
	for (int i = 0; i < RoleItemGroup.Num(); ++i)
	{
		if (RoleItemGroup[i]->RoleInfo.IsLastRole)
		{
			UKBEventData_ReqRemoveRole* EventData = NewObject<UKBEventData_ReqRemoveRole>();
			EventData->RoleInfo = RoleItemGroup[i]->RoleInfo;
			KBENGINE_EVENT_FIRE("ReqRemoveRole", EventData);
			return;
		}
	}

	// ������е�����˵��û��ѡ���κν�ɫ
	DDH::Debug() << "UExRoleWidget::RemoveRoleEvent : No Role Selected" << DDH::Endl();

}

void UExRoleWidget::SureEvent()
{
	EnterGameButton->SetVisibility(ESlateVisibility::Visible);
	RoleTypeBox->SetVisibility(ESlateVisibility::Hidden);

	CreateRoleButton->SetVisibility(ESlateVisibility::Visible);
	RoleNameTextBox->SetVisibility(ESlateVisibility::Hidden);

	RemoveRoleButton->SetVisibility(ESlateVisibility::Visible);
	SureButton->SetVisibility(ESlateVisibility::Hidden);
	CancelButton->SetVisibility(ESlateVisibility::Hidden);

	// ��ȡ�½�ɫ������
	FString RoleName = RoleNameTextBox->GetText().ToString();

	if (RoleName.IsEmpty())
	{
		DDH::Debug() << "Please Input Role Name " << DDH::Endl();
		return;
	}

	// ��ȡ���½�ɫ������
	uint8 RoleType = ShooterCheckBox->GetCheckedState() == ECheckBoxState::Checked ? 0 : 1;
	UKBEventData_ReqCreateRole* EventData = NewObject<UKBEventData_ReqCreateRole>();
	EventData->RoleType = RoleType;
	EventData->Name = RoleName;
	KBENGINE_EVENT_FIRE("ReqCreateRole", EventData);

	// ��������
	RoleNameTextBox->SetText(FText());

}

void UExRoleWidget::CancelEvent()
{
	EnterGameButton->SetVisibility(ESlateVisibility::Visible);
	RoleTypeBox->SetVisibility(ESlateVisibility::Hidden);

	CreateRoleButton->SetVisibility(ESlateVisibility::Visible);
	RoleNameTextBox->SetVisibility(ESlateVisibility::Hidden);

	RemoveRoleButton->SetVisibility(ESlateVisibility::Visible);
	SureButton->SetVisibility(ESlateVisibility::Hidden);
	CancelButton->SetVisibility(ESlateVisibility::Hidden);

	// ��������
	RoleNameTextBox->SetText(FText());
}

void UExRoleWidget::RoleItemSelect(uint64 Dbid)
{
	// ȡ��������ɫ��ѡ��
	for (int i = 0; i < RoleItemGroup.Num(); ++i)
	{
		if (RoleItemGroup[i]->RoleInfo.Dbid != Dbid)
		{
			RoleItemGroup[i]->UnItemSelect();
		}
		else
		{
			RoleItemGroup[i]->ItemSelect();
			// ������ʾ�ڽ����ϵĽ�ɫģ�ͺ�����
			RoleTypeTitle->SetText(RoleTypeName[RoleItemGroup[i]->RoleInfo.RoleType]);
			// ��Ⱦ��ɫͼƬ
			RoleGameMode->RenderActor->SwitchRoleMesh(RoleItemGroup[i]->RoleInfo.RoleType);
		}
	}
}
