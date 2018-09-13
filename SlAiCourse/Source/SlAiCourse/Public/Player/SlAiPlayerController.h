// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SlAiTypes.h"
#include "SlAiPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SLAICOURSE_API ASlAiPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:

	ASlAiPlayerController();

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupInputComponent() override;
	
	// 对Character 的手持物品进行更改， 这个函数在playerState内会调用
	void ChangeHandObject();

public:
	
	// 获取玩家角色
	class ASlAiPlayerCharacter* SPCharacter;
	class ASlAiPlayerState* SPState;

protected:
	virtual void BeginPlay() override;


private:
	
	// 切换视角
	void ChangeView();

	// 鼠标按键事件
	void LeftEventStart();
	void LeftEventStop();
	void RightEventStart();
	void RightEventStop();
	// 滑轮上下滑动事件
	void ScrollUpEvent();
	void ScrollDownEvent();

	// 修改预动作
	void ChangePreUpperType(EUpperBody::Type RightType);

private:

	// 左键预动作
	EUpperBody::Type LeftUpperType;


	// 右键预动作
	EUpperBody::Type RightUpperType;

	// 是否按住左右鼠标键
	bool IsLeftButtonDown;
	bool IsRightButtonDown;
};
