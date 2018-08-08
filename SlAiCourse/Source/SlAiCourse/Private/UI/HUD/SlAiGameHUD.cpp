// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiGameHUD.h"
#include "SWeakWidget.h"
#include "Engine/Engine.h"
#include "SlateBasics.h"
#include "Kismet/GameplayStatics.h"

#include "SSlAiGameHUDWidget.h"
#include "SSlAiShortcutWidget.h"

#include "SlAiPlayerController.h"
#include "SlAiPlayerCharacter.h"
#include "SlAiGameMode.h"
#include "SlAiPlayerState.h"



ASlAiGameHUD::ASlAiGameHUD()
{
	if (!GEngine || !GEngine->GameViewport) return;

	SAssignNew(GameHUDWidget, SSlAiGameHUDWidget);
	GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(GameHUDWidget.ToSharedRef()));

}

void ASlAiGameHUD::BeginPlay()
{
	Super::BeginPlay();

	GM = Cast<ASlAiGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GM) return;
	// ��ȷ��Ҫ���õ�������Ѿ�ʵ��
	GM->InitGamePlayModule();
	// ��ע����������
	GameHUDWidget->ShortcutWidget->RegisterShortcutContainer.BindUObject(GM->SPState, &ASlAiPlayerState::RegistyerShortcutContainer);

}
