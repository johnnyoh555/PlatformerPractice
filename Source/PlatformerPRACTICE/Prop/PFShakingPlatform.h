// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/PFHoverPlatformBase.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PFShakingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERPRACTICE_API APFShakingPlatform : public APFHoverPlatformBase
{
	GENERATED_BODY()

	public:
    APFShakingPlatform();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trigger")
    TObjectPtr<UBoxComponent> TriggerBox;  // 트리거 박스 추가

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

    void StartShaking();  // 흔들리는 애니메이션 시작
    void DropPlatform();  // 발판 추락
    void RespawnPlatform(); // 발판 재생성

    FVector InitialLocation; // 원래 위치 저장
    FRotator InitialRotation; // 원래 회전값 저장
    bool bIsShaking;  // 발판이 흔들리는 중인지 체크

    UPROPERTY(EditAnywhere, Category = "Shaking Platform")
    float ShakeDuration = 1.5f;  // 흔들리는 시간

    UPROPERTY(EditAnywhere, Category = "Shaking Platform")
    float DropDelay = 2.0f;  // 추락까지의 시간

    UPROPERTY(EditAnywhere, Category = "Shaking Platform")
    float RespawnTime = 5.0f;  // 재생성 시간

    FTimerHandle ShakeTimerHandle;
    FTimerHandle DropTimerHandle;
    FTimerHandle RespawnTimerHandle;
};
