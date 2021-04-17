// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuController.h"
#include "MenuWidget.h"
#include <Kismet/GameplayStatics.h>
#include "RPCInstance.h"


void AMenuController::BeginPlay()
{
	Super::BeginPlay();

	// �趨����ģʽ
	bShowMouseCursor = true;
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);

	// ��ȡGameInstance
	URPCInstance* RPCInstance = Cast<URPCInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	RPCInstance->AssignPlayerController(this);


	// ����UI
	UClass* MenuWidgetClass = LoadClass<UMenuWidget>(NULL, TEXT("WidgetBlueprint'/Game/Blueprint/MenuWidget_BP.MenuWidget_BP_C'"));
	UMenuWidget* MenuWidget = CreateWidget<UMenuWidget>(GetWorld(), MenuWidgetClass);
	MenuWidget->AddToViewport();
	MenuWidget->AssignRPCInstance(RPCInstance);

}
