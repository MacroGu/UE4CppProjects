// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <unordered_map>
#include "Monster.generated.h"


class UWidgetComponent;
class UProgressBar;

UCLASS()
class MGMMORPG_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	AMonster(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void MoveToLocation(const FVector& dest);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayAttackMontage();
	UFUNCTION(BlueprintImplementableEvent)
	void Dead();
	UFUNCTION(BlueprintImplementableEvent)
	void HitReact();
	UFUNCTION(BlueprintPure, Category = "UI")
	float GetHealthPercentage();

	// WidgetComponent
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WidgetComponent)
	class UWidgetComponent* WidgetComponent;
	// ���Ա仯
	void OnPropChanged(const int32_t& ID, int32_t Value);
	// ��������
	void SetProp(const int32_t& ID, int32_t Value);
	// ��ȡ����
	int32_t GetProp(const int32_t& ID);

	// ����Ѫ���Ľ���
	void SetHpProgress(float value);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void DelayDestroyMonster();


public:
	bool	IsAttacking;
	int64_t uuid;

	std::unordered_map<int32_t, int32_t> mPropMap;		// ���͵�����
	UPROPERTY()
	UProgressBar* HPBarProgress;

private:
	FTimerHandle DestroyDeadMonsterDelay;		// ��ʱ�����Ѿ������Ĺ���


};
