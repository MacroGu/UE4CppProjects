// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/ExDataMgr.h"
#include "ExGoodItem.generated.h"

class UImage;
class UTextBlock;


// ��BagBlock�Ƴ�ί��
DECLARE_DELEGATE(FLeaveBagBlock)

/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API UExGoodItem : public UUserWidget
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable)
	void InitGoodItem(EBagType InType, uint8 InId);

	// �Ƿ���������
	UFUNCTION(BlueprintCallable, BlueprintPure)
		void IsAllowDragUp(bool& IsAllow);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		void AcceptDragUp(uint8& GoodId, uint8& Number);

	UFUNCTION(BlueprintCallable)
		void LeaveBagBlock();


public:

	UPROPERTY(Meta = (BindWidget))
		UImage* GoodImage;
	
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* NumberText;

	// ���汳�����ͺ͸���ID
	EBagType BagType;

	uint8 BlockId;

	// ί��֪ͨ������BagBlock�Լ��Ѿ����Ƴ�
	FLeaveBagBlock LeaveBagBlockDel;

};
