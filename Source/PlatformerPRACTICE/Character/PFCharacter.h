// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h" // Enhanced Input
#include "Interface/PFCharacterWidgetInterface.h"
#include "Interface/PFCharacterCoinInterface.h"
#include "Interface/PFPortalInteractableInterface.h"
#include "PFCharacter.generated.h"

UCLASS()
class PLATFORMERPRACTICE_API APFCharacter : public ACharacter, public IPFCharacterWidgetInterface, public IPFCharacterCoinInterface,
										public IPFPortalInteractableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APFCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Enhanced Input Actions */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> RunAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	// Camera
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

protected:
	virtual void SetCharacterControlData(const class UPFCharacterControlData* CharacterControlData);

	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPFCharacterControlData> CharacterControlManager;

	// To Change Speed
protected:
	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	float WalkSpeed;

	UPROPERTY(EditAnywhere, Category = CharacterMovement)
	float RunSpeed;

	void StartRunning();
	void StopRunning();

	// 공중에서 속도 변경 오류 해결
protected:
	bool bWantsToRun = false; // 달리기 상태 플래그

	virtual void Landed(const FHitResult& Hit) override;

	// 동전 먹기 기능 추가
protected:
	// UI 위젯 클래스
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPFWidgetComponent> CoinScore;
		
protected:
	// Stat Section
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPFCharacterStatComponent> Stat;

	virtual void SetupCharacterWidget(class UPFUserWidget* InUserWidget) override;

	// Coin Section
protected:
	virtual void TakeCoin() override;

	// RespawnEffect
protected:
	UPROPERTY(EditAnywhere, Category = Effects)
	TObjectPtr<class UNiagaraSystem> RespawnEffect;

	void StartSpawnEffect();
	void UpdateSpawnEffect();

	FTimerHandle MaterialTimerHandle;

public:
	// 리스타트 트리거 메서드
	void TriggerRestart();

protected:
	void Tick(float DeltaTime);

	// 포탈 이동전 효과
protected:
	virtual void ShrinkBeforeTeleport() override;
	virtual void TeleportToNextStage() override;

	FTimerHandle ShrinkTimer;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};