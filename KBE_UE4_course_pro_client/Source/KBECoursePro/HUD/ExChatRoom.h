// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExChatRoom.generated.h"


class USizeBox;
class UScrollBox;
class UEditableText;
class UExChatItem;
class UKBEventData;


/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API UExChatRoom : public UUserWidget
{
	GENERATED_BODY()
	
public:


	// ��MmoWidget����ע���¼�
	void InstallEvent();

	// ע���¼�
	void UnInstallEvents();

	// ��ʾ���������
	void ShowOrHideInput(bool IsShow);

	UFUNCTION(BlueprintCallable)
		void SendChatInfo();

	void AcceptChatList(const UKBEventData* EventData);

public:

	UPROPERTY(Meta = (BindWidget))
		USizeBox* ChatInputBox;

	UPROPERTY(Meta = (BindWidget))
		UScrollBox* ChatScrollBox;

	UPROPERTY(Meta = (BindWidget))
		UEditableText* InputTextBox;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UExChatItem> ChatItemClass;


};
