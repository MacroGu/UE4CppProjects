// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlAiTypes.h"
#include "CoreMinimal.h"

class USoundCue;

/**
 * 
 */
class SLAICOURSE_API SlAiDataHandle
{
public:
	SlAiDataHandle();

	static void Initialize();

	static TSharedPtr<SlAiDataHandle> Get();

	// �޸���Ӣ��
	void ChangeLocalizationCulture(ECultureTeam Culture);
	// �޸Ĳ˵�����
	void ResetMenuVolume(float MusicVol, float SoundVol);



public:
	ECultureTeam CurrentCulture;
	float MusicVolume;	// ������С
	float SoundVolume;	// ��Ч��С
	// �浵����
	TArray<FString> RecordDataList;
	// �浵��
	FString RecordName;

private:
	// ��������
	static TSharedRef<SlAiDataHandle> Create();

	// ����enum���ͻ�ȡ�ַ���
	template<typename TEnum>
	FString GetEnumValueAsString(const FString& Name, TEnum Value);

	// �����ַ�������ȡ Enum ֵ
	template<typename TEnum>
	TEnum GetEnumValueFromString(const FString& EnumName, FString String);

	// ��ʼ���浵����
	void InitRecordData();
	// ��ʼ��Menu��������
	void InitializedMenuAudio();


private:
	static TSharedPtr<SlAiDataHandle> DataInstance;
	// ���� Menu ������
	TMap<FString, TArray<USoundCue*>> MenuAudioResource;
	// ��ȡMenuStyle, �������������ļ�
	const struct FSlAiMenuStyle* MenuStyle;


};
