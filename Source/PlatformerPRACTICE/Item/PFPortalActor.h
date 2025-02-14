// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PFPortalActor.generated.h"

UCLASS()
class PLATFORMERPRACTICE_API APFPortalActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APFPortalActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void LoadPortalEffect();

public:	
	// 포탈 활성화 상태
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Portal)
	bool bIsActivated;

	// 포탈 활성화 함수
	UFUNCTION(BlueprintCallable, Category = Portal)
	void ActivatePortal();

	// Next Stage
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Portal)
	FName TargetMapName; // 이동할 맵 이름 설정

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

protected:
	// 나이아가라 이펙트 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = Components)
	class UNiagaraComponent* PortalEffect;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<class UStaticMeshComponent> Body;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<class UStaticMeshComponent> Ring;

	UPROPERTY(VisibleAnywhere, Category = Components)
	TObjectPtr<class UBoxComponent> CollisionBox; // 충돌 감지를 위한 박스 컴포넌트

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Portal, meta = (AllowPrivateAccess = "true"))
	bool bIsActive; // 포탈 활성화 상태 관리
};
