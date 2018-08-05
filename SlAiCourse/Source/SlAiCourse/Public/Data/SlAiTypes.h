// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBorder.h"
#include "STextBlock.h"
#include "SImage.h"
#include "SlateBasics.h"


/**
 * 
 */
UENUM()
enum class ECultureTeam : uint8 
{
	EN = 0,
	ZH = 1
};


// Menu ��ť������
namespace EMenuItem
{
	enum Type
	{
		None,
		StartGame,
		GameOption,
		QuitGame,
		NewGame,
		LoadRecord,
		StartGameGoBack,
		GameOptionGoBack,
		NewGameGoBack,
		ChooseRecordGoBack,
		EnterGame,
		EnterRecord
	};
};


// Menu ��������
namespace EMenuType
{
	enum Type
	{
		None = 0,
		MainMenu,
		StartGame,
		GameOption,
		NewGame,
		ChooseRecord
	};
}

// Menu ����״̬ö��
namespace EMenuAnim
{
	enum Type
	{
		Stop,		// ֹͣ����
		Close,		// �ر�Menu
		Open		// ��Menu
	};
}

// �ӽ�ģʽ
namespace EGameViewMode
{
	enum Type
	{
		First,
		Third
	};
}

// �ϰ�������״̬
namespace EUpperBody
{
	enum Type
	{
		None,
		Punch,
		Hit,
		Fight,
		PickUp,
		Eat
	};
}

// ��Ʒ����
namespace EObjectType
{
	enum Type
	{
		Normal = 0,			// ��ͨ��Ʒ��ľͷ��ʯͷ
		Food,		// ʳ�ƻ����
		Tool,		// ���ߣ� ���ӣ� ����
		Weapon		// ��������
	};
}


// ��Ʒ���Խṹ��
struct ObjectAttribute
{
	FText EN;		// Ӣ����
	FText ZH;		// ������
	EObjectType::Type ObjectType;		// ��Ʒ����
	int PlantAttack;		// ��ֲ��Ĺ�����
	int MetalAttack;		// �Խ�����Դ�Ĺ�����
	int AnimalAttack;		// �Զ���Ĺ�����
	int AffectRange;		// ��������
	FString TexPath;		// ͼƬ·��

	// ���캯��
	ObjectAttribute(const FText ENName, const FText ZHName, const EObjectType::Type OT, const int PA, const int MA, const int AA, const int AR, const FString TP)
	{
		EN = ENName;
		ZH = ZHName;
		ObjectType = OT;
		PlantAttack = PA;
		MetalAttack = MA;
		AnimalAttack = AA;
		AffectRange = AR;
		TexPath = TP;
	}

// 	FString ToString()
// 	{
// 		return EN.ToString() + FString("--") + ZH.ToString() + FString("--") + FString::FromInt((int)ObjectType) + FString("--") + FString::FromInt((int)PlantAttack) + FString("--") + FString::FromInt((int)MetalAttack) + FString("--") + FString::FromInt((int)AnimalAttack) + FString("--") + FString::FromInt((int)AffectRange) + FString("--") + TexPath;
// 	}
};


// ����������Ľṹ��
struct ShortcutContainer
{
	// ��ƷID
	int ObjectIndex;
	int ObjectNum;
	TSharedPtr<SBorder> ContainerBorder;
	TSharedPtr<SBorder> ObjectImage;
	TSharedPtr<STextBlock> ObjectNumText;
	const FSlateBrush* NormalContainerBrush;
	const FSlateBrush* ChoosedContainerBrush;
	TArray<const FSlateBrush*>* ObjectBrushList;

	ShortcutContainer(TSharedPtr<SBorder> CB, TSharedPtr<SBorder> OI, TSharedPtr<STextBlock> ONT, const FSlateBrush* NCB, const FSlateBrush* CCB, TArray<const FSlateBrush*>* OBL)
	{
		ContainerBorder = CB;
		ObjectImage = OI;
		ObjectNumText = ONT;
		NormalContainerBrush = NCB;
		ChoosedContainerBrush = CCB;
		ObjectBrushList = OBL;


		// ��ʼ����ʾ����
		ObjectIndex = 0;
		ObjectNum = 0;
		ContainerBorder->SetBorderImage(NormalContainerBrush);
		ObjectImage->SetBorderImage((*ObjectBrushList)[0]);
	}

	// �����Ƿ�ѡ�е�ǰ����Ʒ�� true ����Ҫѡ�У� ������Ʒ����
	int SetChoosed(bool Option)
	{
		if (Option)
		{
			ContainerBorder->SetBorderImage(ChoosedContainerBrush);
		}
		else
		{
			ContainerBorder->SetBorderImage(NormalContainerBrush);
		}
		return ObjectIndex;
	}

	// ����Index
	ShortcutContainer* SetObject(int NewIndex)
	{
		ObjectIndex = NewIndex;
		ObjectImage->SetBorderImage((*ObjectBrushList)[ObjectIndex]);
		return this;
	}

	// ��������
	ShortcutContainer* SetObjectNum(int Num = 0)
	{
		ObjectNum = Num;
		// ����Ϊ0 ����1�� ����ʾ����
		if (ObjectNum == 0 || ObjectNum == 1)
		{
			ObjectNumText->SetText(FString(""));
		}
		else
		{
			ObjectNumText->SetText(FString::FromInt(ObjectNum));
		}

		return this;
	}
};

