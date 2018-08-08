// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SlAiTypes.h"
#include "SlAiPlayerState.generated.h"

class STextBlock;

/**
 * 
 */
UCLASS()
class SLAICOURSE_API ASlAiPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ASlAiPlayerState();
	
	// �ṩ��ShortcutWdiget����ӿ��������ί��
	void RegistyerShortcutContainer(TArray<TSharedPtr<ShortcutContainer>>* ContainerList, TSharedPtr<STextBlock> ShortcutInfoTextBlock);
	

private:
	// ��ȡ�������Ʒ��Ϣ
	FText GetShortcutInfoText() const;

private:
	
	// ���������
	TArray<TSharedPtr<ShortcutContainer>> ShortcutContainerList;

	// �������Ϣ����
	TAttribute<FText> ShortcutInfoTextAttr;

};
