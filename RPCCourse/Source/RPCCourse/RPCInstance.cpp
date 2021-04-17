// Fill out your copyright notice in the Description page of Project Settings.


#include "RPCInstance.h"
#include "../Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineSessionInterface.h"
#include "../Plugins/Online/OnlineSubsystemUtils/Source/OnlineSubsystemUtils/Public/OnlineSubsystemUtils.h"
#include <GameFramework/PlayerController.h>
#include "ExCommon.h"
#include <UObject/CoreOnline.h>
#include "../Plugins/Online/OnlineSubsystem/Source/Public/OnlineSubsystem.h"
#include "../Plugins/Online/OnlineSubsystem/Source/Public/OnlineSessionSettings.h"
#include <Delegates/IDelegateInstance.h>
#include <Kismet/GameplayStatics.h>



URPCInstance::URPCInstance()
{
	// �󶨻ص�����
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &URPCInstance::OnCreateSessionComplete);
	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &URPCInstance::OnStartOnlineGameComplete);

	OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &URPCInstance::OnFindSessionComplete);
	OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &URPCInstance::OnJoinSessionComplete);
	OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &URPCInstance::OnDestroySessionComplete);

}

void URPCInstance::AssignPlayerController(APlayerController* InController)
{
	PlayerController = InController;

	// ��ȡOnlineSub
	// ��ȡ��ʽһ��Online::GetSubsystem(GetWorld(), NAME_None); �Ƽ���ʽ
	// ��ȡ��ʽ����ʹ��IOnlineSubsystem::Get(), ֱ�ӻ�ȡ����createSession����joinSession��ͻ���û����ת����
	OnlineSub = Online::GetSubsystem(PlayerController->GetWorld(), NAME_None);

	// ��ȡUserID
	// ��ȡ��ʽһ�� UGameplayStatics::GetGameInstance(GetWorld())->GetLocalPlayer()[0]->GetPreferredUniqueNetId()
	if (GetLocalPlayers().Num() == 0)
	{
		DDH::Debug() << "No LocalPlayer Exis, Can't Get UserID" << DDH::Endl();
	}
	else
	{
		UserID = (*GetLocalPlayers()[0]->GetPreferredUniqueNetId()).AsShared();
	}


#if 0
	// ��ȡ��ʽ���� ʹ��PlayerState��ȡ, �÷�ʽ�����exeû�����⣬ �ڱ༭��ģʽ�¶�����ڻ��Ҳ��� Playerstate
	if (PlayerController->PlayerState)
	{
		UserID = PlayerController->PlayerState->UniqueId.GetUniqueNetId();
	}
#endif

	// ������ֱ�ӻ�ȡ Session ����ʱ�ᱨ���������ڵ�����



}

void URPCInstance::HostSession()
{
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			// �Ự����
			FOnlineSessionSettings Settings;
			// ������
			Settings.NumPublicConnections = 10;
			Settings.bShouldAdvertise = true;
			Settings.bAllowJoinInProgress = true;
			// ʹ�þ�����
			Settings.bIsLANMatch = true;
			Settings.bUsesPresence = true;
			Settings.bAllowJoinViaPresence = true;
			// ��ί��
			OnCreateSessionCompleteDelegateHandle = Session->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);
			// �����滭
			Session->CreateSession(*UserID, NAME_GameSession, Settings);

		}
	}
}

void URPCInstance::ClientSession()
{
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			// ʵ�����������ָ�벢���趨����
			SearchObject = MakeShareable(new FOnlineSessionSearch);
			// ���ؽ��
			SearchObject->MaxSearchResults = 10;
			// �Ƿ��Ǿ����������� IsLAN
			SearchObject->bIsLanQuery = true;
			SearchObject->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
			// ��Ѱ�һỰί��
			OnFindSessionsCompleteDelegateHandle = Session->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);
			// ���лỰѰ��
			Session->FindSessions(*UserID, SearchObject.ToSharedRef());

		}

	}
}

void URPCInstance::DestroySession()
{
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			// �����ٻỰί��
			OnDestroySessionCompleteDelegateHandle = Session->AddOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegate);
			// ִ�����ٻỰ
			Session->DestroySession(NAME_GameSession);
		}
	}

}

void URPCInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			// ����󶨻滭��ɻص�����
			Session->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
			// �жϴ����Ự�Ƿ�ɹ�
			if (bWasSuccessful)
			{
				DDH::Debug() << "CreateSession Succeed" << DDH::Endl();

				// �󶨿����Ựί��
				OnStartSessionCompleteDelegateHandle = Session->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);
				Session->StartSession(NAME_GameSession);
			}
			else
			{
				DDH::Debug() << "CreateSession Failed" << DDH::Endl();
			}
		}
	}
}

void URPCInstance::OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful)
{
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			// ע�������Ựί�а�
			Session->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
			if (bWasSuccessful)
			{
				DDH::Debug() << "StartSession Succeed" << DDH::Endl();
				// �������ת����
				UGameplayStatics::OpenLevel(PlayerController->GetWorld(), FName("GameMap"), true, FString("listen"));
			}
			else
			{
				DDH::Debug() << "StartSession Failed" << DDH::Endl();
			}
		}

	}
}

void URPCInstance::OnFindSessionComplete(bool bWasSuccessful)
{
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			// ȡ��Ѱ�һỰί�а�
			Session->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegateHandle);
			// ���Ѱ�һỰ�ɹ�
			if (bWasSuccessful)
			{
				//����ռ��Ľṹ���ڲ��Ҵ���1
				if (SearchObject.IsValid() && SearchObject->SearchResults.Num() > 0)
				{
					DDH::Debug() << "Find Session Succeed" << DDH::Endl();
					// �󶨼���sessionί��
					OnJoinSessionCompleteDelegateHandle = Session->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);
					// ִ�м���session
					Session->JoinSession(*UserID, NAME_GameSession, SearchObject->SearchResults[0]);
				}
				else
				{
					DDH::Debug() << "Find Session Succeed But Num == 0" << DDH::Endl();
				}
			}
			else
			{
				DDH::Debug() << "Find Session Failed" << DDH::Endl();
			}

		}

	}
}

void URPCInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			// ȡ������Ựί�а�
			Session->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegateHandle);
			// �������ɹ�
			if (Result == EOnJoinSessionCompleteResult::Success)
			{
				// ������ҵ��µ�ͼ
				FString ConnectString;
				if (Session->GetResolvedConnectString(NAME_GameSession, ConnectString))
				{
					DDH::Debug() << "Join Sessions Succeed " << DDH::Endl();
					// �ͻ����л����������Ĺؿ�
					PlayerController->ClientTravel(ConnectString, TRAVEL_Absolute);
				}

			}

		}

	}
}

void URPCInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			// ȡ�����ٻỰί��
			Session->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegateHandle);
			// �����߼���������

		}
	}
}
