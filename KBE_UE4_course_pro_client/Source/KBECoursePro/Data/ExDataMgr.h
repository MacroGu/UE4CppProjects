// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ExDataAsset.h"
#include "ExDataMgr.generated.h"

class UExGoodDrag;

UENUM()
enum class EBagType : uint8
{
	MainBag = 0,
	SkillBag,
	BuffBag,
	EquipBag
};

UENUM()
enum class EGoodType : uint8
{
	Skill = 0,
	Buff,
	Equip
};

USTRUCT()
struct FGoodInfo
{
	GENERATED_BODY()

public:

	UPROPERTY()
		uint8 BlockId;

	UPROPERTY()
		uint8 GoodId;

	UPROPERTY()
		EGoodType GoodType;

	UPROPERTY()
		uint8 GoodKind;

	UPROPERTY()
		uint8 Number;

	FGoodInfo() {}

	void InitInfo(uint8 InBlockId, uint8 InGoodId, uint8 InNumber);

	bool IsEmpty() const {
		return Number == 0;
	}

};

struct FGoodData
{
	EGoodType GoodType;

	uint8 GoodKind;

	FGoodData(EGoodType InType, uint8 InKind) : GoodType(InType), GoodKind(InKind) {}

};


// ���±�����Ʒ����ˢ��UI�� ί��
DECLARE_DELEGATE_TwoParams(FUpdateBagBlock, EBagType, uint8)

/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API UExDataMgr : public UObject
{
	GENERATED_BODY()
	

public:

	static UExDataMgr* Get();

	void LoadTotalData();

	// ��ȡ���ݺ���
	UTexture* GetGoodTexture(int32 InIndex);

	uint8 GetKindByGoodId(uint8 GoodId);

	EGoodType GetTypeByGoodId(uint8 GoodId);

	void ChangeGoodInfo(EBagType BagType, FGoodInfo GoodInfo);

	bool IsGoodExist(EBagType BagType, uint8 BlockId) const;

	const FGoodInfo GetGoodInfo(EBagType BagType, uint8 BlockId) const;

	// �����Ƿ�����Ʒ
	bool IsHandGoodExist();

	// �����Ƿ�����Ʒ�����ҷ�����Ʒ��Ϣ
	FGoodInfo GetHandGoodInfo() const;

	// ����������Ʒ���û���ק��
	void ReviseHandGood();


public:

	UPROPERTY()
		TMap<uint8, FGoodInfo> SkillBag;

	UPROPERTY()
		TMap<uint8, FGoodInfo> BuffBag;

	UPROPERTY()
		TMap<uint8, FGoodInfo> EquipBag;

	UPROPERTY()
		TMap<uint8, FGoodInfo> MainBag;

	// ��Ʒ���ϱ� key ��Ʒid
	TMap<uint8, FGoodData> GoodDatas;

	FUpdateBagBlock UpdateBagBlockDel;

	// ���浱ǰ�������ŵ���Ʒ��������
	EBagType HandBagType;

	// ���浱ǰ�������ŵ���Ʒ����ID
	uint8 HandBlockId;

	// �����������ƶ�����ƷUI�����������ж������Ƿ�����Ʒ
	UPROPERTY()
		UExGoodDrag* GoodDrag;

	uint8 CurrentOnSkill;

protected:

	UPROPERTY()
		UExDataAsset* TotalData;

	static UExDataMgr* MgrInst;
};
