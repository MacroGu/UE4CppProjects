// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlAiTypes.h"
#include "Json.h"


/**
 * 
 */
class SLAICOURSE_API SlAiJsonHandle
{
public:
	SlAiJsonHandle();

	// �����浵����
	void RecordDataJsonRead(FString& Culture, float& MusicVolume, float& SoundVolume, TArray<FString>& RecordDataList);


	// �޸Ĵ浵
	TSharedPtr<FJsonObject> UpdateRecordData(FString Culture, float MusicVolume, float SoundVolume, TArray<FString>* RecordDataList);

	// ������Ʒ����
	void ObjectAttrJsonRead(TMap<int, TSharedPtr<ObjectAttribute>>& ObjectAttrMap);

	// ������Դ����
	void ResourceAttrJsonRead(TMap<int, TSharedPtr<ResourceAttribute>>& ResourceAttrMap);


private:
	
	// ��ȡJson �ļ����ַ���
	bool LoadStringFromFile(const FString& FileName, const FString& RelaPath, FString& ResultString);

	// FJsonObject ת����Json��ʽ���ַ���
	bool GetFStringInJsonData(const TSharedPtr<FJsonObject>& JsonObj, FString& JsonStr);

	// �����ַ������ļ�
	bool WriteFileWithJsonData(const FString& JsonStr, const FString& RelaPath, const FString& FileName);

	// ����һ����string ת����objecttype �ķ���
	EObjectType::Type StringToObjectType(const FString ArgStr);

	// ����һ����stringת����ResourceType�ķ���
	EResourceType::Type StringToResourceType(const FString ArgStr);



private:
	// �浵�ļ���
	FString RecordDataFileName;

	// ��Ʒ�����ļ���
	FString ObjectAttrFileName;

	// ��Դ�����ļ���
	FString ResourceAttrFileName;

	// ���·��
	FString RelativePath;

};
