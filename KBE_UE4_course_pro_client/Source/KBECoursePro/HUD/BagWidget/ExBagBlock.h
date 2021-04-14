// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/ExDataMgr.h"
#include "ExBagBlock.generated.h"

class UExGoodItem;
class UOverlay;


/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API UExBagBlock : public UUserWidget
{
	GENERATED_BODY()
	

public:

	void UpdateBlock();

	// ��ʼ������������Id
	UFUNCTION(BlueprintCallable)
		void InitBlockInfo(EBagType InType, uint8 InId);

	// �Ƿ����������Ʒ
	UFUNCTION(BlueprintCallable, BlueprintPure)
		void IsAllowDropDown(bool& DropResult);

	// �����������ת����Ʒ��ͬʱ������һ���µ�GoodItem��ӵ�����
	UFUNCTION(BlueprintCallable)
		void RequestPassGood();

	// ����Ʒ�Ż�ԭ����
	UFUNCTION(BlueprintCallable)
		void ReviseDragGood();

public:

	UPROPERTY(BlueprintReadOnly)
		EBagType BagType;

	UPROPERTY(BlueprintReadOnly)
		uint8 BlockId;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UExGoodItem> GoodItemClass;

	UPROPERTY(BlueprintReadWrite)
		UExGoodItem* GoodItem;

	UPROPERTY(Meta = (BindWidget))
		UOverlay* RootBox;

};
