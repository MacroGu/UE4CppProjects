// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Center/ExKbeGameMode.h"
#include "ExLoginGameMode.generated.h"

class UKBEMain;
class UExLoginWidget;
class UKBEventData;

/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API AExLoginGameMode : public AExKbeGameMode
{
	GENERATED_BODY()

public:

	virtual void InstallEvent() override;

public:

	UKBEMain* KBEMain;


protected:

	virtual void BeginPlay() override;

	/* KBE�¼�
	*/
	void OnCreateAccountResult(const UKBEventData* pEventData);

	/* KBE�¼�
	*/
	void OnLoginFailed(const UKBEventData* pEventData);

	/* KBE�¼�
	*/
	void OnVersionNotMatch(const UKBEventData* pEventData);

	/* KBE�¼�
	*/
	void OnScriptVersionNotMatch(const UKBEventData* pEventData);

	/* KBE�¼�
	*/
	void OnLoginBaseappFailed(const UKBEventData* pEventData);

	/* KBE�¼�
	*/
	void OnLoginBaseapp(const UKBEventData* pEventData);

	/* KBE�¼�
	*/
	void OnLoginSuccessfully(const UKBEventData* pEventData);

protected:

	UExLoginWidget* LoginWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UExLoginWidget> LoginWidgetClass;


};

