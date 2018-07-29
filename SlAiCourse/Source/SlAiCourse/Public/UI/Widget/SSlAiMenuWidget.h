// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlAiTypes.h"
#include "Widgets/SCompoundWidget.h"


class SBox;
class STextBlock;
class SVerticalBox;
struct MenuGroup;
class SSlAiGameOptionWidget;
class SSlAiNewGameWidget;
class SSlAiChooseRecordWidget;

/**
 * 
 */
class SLAICOURSE_API SSlAiMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiMenuWidget)
	{}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);


private:
	// �󶨵�����MenuItem�ķ���
	void MenuItemOnClicked(EMenuItem::Type ItemType);
	// �޸�����
	void ChangeCulture(ECultureTeam Culture);
	// �޸�����
	void ChangeVolume(const float MusicVolume, const float SoundVolume);
	// ��ʼ�����еĿؼ�
	void InitializeMenuList();
	// ѡ����ʾ�Ľ���
	void ChooseWidget(EMenuType::Type WidgetType);
	// �޸Ĳ˵��Ĵ�С
	void ResetWidgetSize(float NewWidth, float NewHeight);

private:

	// ������ڵ�
	TSharedPtr<SBox> RootSizeBox;
	// ����MenuStyle
	const struct FSlAiMenuStyle* MenuStyle;
	// �������
	TSharedPtr<STextBlock> TitleText;
	// �������洹ֱ�б�
	TSharedPtr<SVerticalBox> ContentBox;
	// ����˵���
	TMap<EMenuType::Type, TSharedPtr<MenuGroup>> MenuMap;
	// ��Ϸ����Widget ��ָ��
	TSharedPtr<SSlAiGameOptionWidget> GameOptionWidget;
	// ����Ϸ�ؼ�ָ��
	TSharedPtr<SSlAiNewGameWidget> NewGameWidget;
	// ѡ��浵�ؼ�ָ��
	TSharedPtr<SSlAiChooseRecordWidget> ChooseRecordWidget;

};
