// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "ExRoleWidget.generated.h"

class AExRoleGameMode;
class UButton;
class UHorizontalBox;
class UEditableTextBox;
class UScrollBox;
class UCheckBox;
struct FROLE_INFO;
class UExRoleItem;
class UTextBlock;


/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API UExRoleWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	void OnReqRoleList(TArray<FROLE_INFO> RoleList);

	void OnCreateRole(FROLE_INFO RoleInfo);

	void OnRemoveRole(FROLE_INFO RoleInfo);

	UFUNCTION(BlueprintCallable)
		void EnterGameEvent();

	UFUNCTION(BlueprintCallable)
		void CreateRoleEvent();

	UFUNCTION(BlueprintCallable)
		void RemoveRoleEvent();

	UFUNCTION(BlueprintCallable)
		void SureEvent();

	UFUNCTION(BlueprintCallable)
		void CancelEvent();

public:

	UPROPERTY(EditAnywhere)
		TSubclassOf<UExRoleItem> RoleItemClass;

	AExRoleGameMode* RoleGameMode;

	UPROPERTY(Meta = (BindWidget))
		UScrollBox* RoleItemScroll;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* RoleTypeTitle;

	// �������ĵ�  ���� ��ʦ
	UPROPERTY(EditAnywhere)
		TArray<FText> RoleTypeName;

	// ��ť��CheckBox, TextBox
	UPROPERTY(Meta = (BindWidget))
		UButton* EnterGameButton;

	UPROPERTY(Meta = (BindWidget))
		UButton* CreateRoleButton;

	UPROPERTY(Meta = (BindWidget))
		UButton* RemoveRoleButton;

	UPROPERTY(Meta = (BindWidget))
		UButton* SureButton;

	UPROPERTY(Meta = (BindWidget))
		UButton* CancelButton;

	UPROPERTY(Meta = (BindWidget))
		UHorizontalBox* RoleTypeBox;

	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* RoleNameTextBox;

	// ��ȡ��ѡ�������жϵ�ǰѡ�����ĸ���ɫ����
	UPROPERTY(Meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
		UCheckBox* ShooterCheckBox;


protected:

	void RoleItemSelect(uint64 Dbid);

protected:

	UPROPERTY()
		TArray<UExRoleItem*> RoleItemGroup;

};
