// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PFHoverPlatformBase.generated.h"

UCLASS(Abstract) // 추상 클래스로 선언
class PLATFORMERPRACTICE_API APFHoverPlatformBase : public AActor
{
	GENERATED_BODY()
	
public:
    APFHoverPlatformBase();

    UFUNCTION(BlueprintCallable, Category = HoverPlatform)
    void ActivatePlatform();

    UFUNCTION(BlueprintCallable, Category = HoverPlatform)
    void DeactivatePlatform();

    UPROPERTY(EditAnywhere, Category = "HoverPlatform|Movement")
    float Speed;

    UPROPERTY(EditAnywhere, Category = "HoverPlatform|Movement")
    float DelayBeforeStart;

protected:
    virtual void BeginPlay() override;

    // 매쉬 컴포넌트 추가
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> PlatformMesh;

    UPROPERTY(EditAnywhere, Category = "HoverPlatform|Movement")
    bool bIsActive;

    UPROPERTY(EditAnywhere, Category = "HoverPlatform|Movement")
    FVector TargetLocation;

    FVector StartLocation;
};
