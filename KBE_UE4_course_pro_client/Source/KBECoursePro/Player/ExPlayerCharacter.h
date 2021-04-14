// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/ExCharacterEntity.h"
#include "ExPlayerCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class AExMmoController;
class UExMmoWidget;
class USceneComponent;

/**
 * 
 */
UCLASS()
class KBECOURSEPRO_API AExPlayerCharacter : public AExCharacterEntity
{
	GENERATED_BODY()
	

public:

	AExPlayerCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	virtual void Tick(float DeltaSeconds) override;

	virtual void Destroyed() override;

	virtual void SetBaseHP(int32 InBaseHP) override;

	virtual void SetHP(int32 InHP) override;

	void SetSpeedRatio(float InSpeedRatio);

	void Attack(uint8 SkillId);

public:
	AExMmoController* MmoController;

	UPROPERTY(EditAnywhere)
		UExMmoWidget* MmoWidget;

	UPROPERTY(EditAnywhere)
		float TurnRate;

	UPROPERTY(EditAnywhere)
		float LookUpRate;

protected:

	virtual void BeginPlay() override;

	void DoJump();

	void DoStopJump();

	void MoveForward(float Value);

	void MoveRight(float Value);

	void Turn(float Value);

	void LookUp(float Value);

	void AnimUpdate();

	void OperateBag();

	// ���󹥻�
	void RequestAttack();

	// ������ʱ�䣬�����л�ѡ�еļ���
	void ScrollUp();

	void ScrollDown();

	// ����Buff�Ĵ����¼�
	void BuffOne();

	void BuffTwo();

	void BuffThree();

	void RequestBuff(uint8 BlockId);

protected:

	UPROPERTY(EditAnywhere)
		USpringArmComponent* CameraBoom;
	
	UPROPERTY(EditAnywhere)
		UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere)
		USceneComponent* SkillPoint;

	// ���¶���������˶�ʱ�����
	FTimerHandle AnimUpdateHandle;

	bool IsShowBag;
};
