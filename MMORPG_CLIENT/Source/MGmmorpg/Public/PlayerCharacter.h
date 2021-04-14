// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;
class UWidgetComponent;
class UProgressBar;


UCLASS()
class MGMMORPG_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()
		/** Camera boom positioning the camera behind the character */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	// ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties")
		float HealthValue;

	// ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties")
		float EnergyValue;

	// ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties")
		float MoodValue;

	UFUNCTION(BlueprintCallable)
		void HitOtherCharacter();

	UPROPERTY()
		UProgressBar* HPBarProgress;

public:
	bool	IsAttacking;
	int32_t	SessionID;
	int64_t	uuid;		// ����ҵ�ΨһID
	
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// �������ߵĶ���
	void PlayMoveWalkMontage(const bool& need_brocast, const FVector& new_location);
	void DestroyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ��ʱ�ü����ƶ�����
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);


	void GenerateNewPlayer();

	void SimulatePlayerRun();


private:
	int64_t last_move_time;			// ���Ƽ��̰����ƶ���ʱ��

	// �жϵ�ǰ�Ƿ����ͨ�����̽����ƶ�
	bool CanMoveByHitKeyBoard();


};
