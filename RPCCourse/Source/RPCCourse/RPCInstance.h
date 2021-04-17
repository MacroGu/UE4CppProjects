// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Delegates/IDelegateInstance.h"
#include "RPCInstance.generated.h"


class IOnlineSubsystem;
class APlayerController;

/**
 * 
 */
UCLASS()
class RPCCOURSE_API URPCInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	URPCInstance();

	void AssignPlayerController(APlayerController* InController);

	void HostSession();

	void ClientSession();

	void DestroySession();

protected:

	// �����������ص�����
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);

	// ����������ص�����
	void OnFindSessionComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	// ���ٻỰ�ص�����
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

protected:

	APlayerController* PlayerController;

	// ����������ί������
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;

	// ���������ί������
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

	FDelegateHandle OnFindSessionsCompleteDelegateHandle;
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;

	// ���ٻỰί������
	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;


	IOnlineSubsystem* OnlineSub;

	TSharedPtr<const FUniqueNetId> UserID;

	// ����Ѱ�ҵ���Sessions
	TSharedPtr<FOnlineSessionSearch> SearchObject;

};
