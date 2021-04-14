// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ExCharacterEntity.generated.h"

class AExMmoGameMode;
class UAnimInstance;
class UAnimMontage;

UCLASS()
class KBECOURSEPRO_API AExCharacterEntity : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AExCharacterEntity();

	virtual void Destroyed() override;

	void SetTargetPosition(FVector InPos);

	void SetTargetRotator(FRotator InRot);

	// ����Ŀ�궯���ĺ���
	void SetTargetAnim(float Speed, float Direction);

	virtual void SetBaseHP(int32 InBaseHP) {}

	virtual void SetHP(int32 InHP) {}

	void OnAttack();

public:

	int32 EntityId;

	uint8 RoleType;

	FString RoleName;

	AExMmoGameMode* MmoGameMode;

	bool IsPlayer;

	UPROPERTY(BlueprintReadOnly)
		float AnimSpeed;

	UPROPERTY(BlueprintReadOnly)
		float AnimDirection;

	UPROPERTY(BlueprintReadOnly)
		bool AnimIsInAir;

	UPROPERTY(BlueprintReadOnly)
		int32 HP;

	int32 BaseHP;

	UPROPERTY(EditAnywhere)
		UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere)
		UAnimMontage* HurtMontage;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	// Ŀ��λ��
	FVector TargetPosition;

	// Ŀ��ѡ��
	FRotator TargetRotator;

	// ��һ�θ���λ�õ�ʱ��
	float LastUpdatePositionTime;

	float MoveSpeed;

	// ��һ��ͬ��������ʱ��
	float LastUpdateAnimTime;

	// ���¶���ʱ����
	float UpdateAnimSpaceTime;

	// ʣ�ද������ʱ��
	float RemainAnimSpaceTime;

	// Ŀ���ٶȺ��ƶ��Ƕ�
	float TargetSpeed;

	float TargetDirection;

	// ��һ�ε��ٶ����ƶ��Ƕ�
	float LastSpeed;

	float LastDirection;

	// ���涯����ͼ
	UAnimInstance* CharacterAnim;

};
