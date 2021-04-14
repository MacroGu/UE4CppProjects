// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ExChatRoom.h"
#include "Scripts/ExEventData.h"
#include "ExChatItem.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"
#include "Components/SizeBox.h"
#include "Components/ScrollBoxSlot.h"




void UExChatRoom::InstallEvent()
{
	// ��Զ�̻ص������� ע���˵��¼��ڹؿ�����ʱһ��Ҫע��
	KBENGINE_REGISTER_EVENT("AcceptChatList", AcceptChatList);
}

void UExChatRoom::UnInstallEvents()
{
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void UExChatRoom::ShowOrHideInput(bool IsShow)
{
	if (IsShow)
	{
		ChatInputBox->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ChatInputBox->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UExChatRoom::SendChatInfo()
{
	// ��ȡ�����ַ�����������
	FString Message = InputTextBox->GetText().ToString();
	InputTextBox->SetText(FText());

	// ��������ַ���Ϊ�գ� ����
	if (!Message.IsEmpty())
	{
		UKBEventData_SendChatInfo* EventData = NewObject<UKBEventData_SendChatInfo>();
		EventData->Message = Message;
		KBENGINE_EVENT_FIRE("SendChatInfo", EventData);
	}

}

void UExChatRoom::AcceptChatList(const UKBEventData* EventData)
{
	const UKBEventData_AcceptChatList* ServerData = Cast<UKBEventData_AcceptChatList>(EventData);

	// ���������µ�ChatItem��䵽ScrollBox
	for (auto Info : ServerData->ChatList)
	{
		UExChatItem* ChatItem = CreateWidget<UExChatItem>(this, ChatItemClass);
		ChatItem->InitItem(Info.Name, Info.Date, Info.Message);

		UScrollBoxSlot* ItemSlot = Cast<UScrollBoxSlot>(ChatScrollBox->AddChild(ChatItem));
		ItemSlot->SetHorizontalAlignment(HAlign_Fill);
		ItemSlot->SetVerticalAlignment(VAlign_Bottom);
		ItemSlot->SetPadding(FMargin(0.f, 20.f, 0.f, 0.f));

	}

	// �ƶ�����������Ͳ�
	ChatScrollBox->ScrollToEnd();

}
