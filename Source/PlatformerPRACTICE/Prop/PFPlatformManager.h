// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PFPlatformManager.generated.h"

UCLASS()
class PLATFORMERPRACTICE_API APFPlatformManager : public AActor
{
    GENERATED_BODY()

    public:
    APFPlatformManager();

protected:
    virtual void BeginPlay() override;

public:
    // 데이터 테이블을 지정할 수 있도록 설정
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform")
    TObjectPtr<class UDataTable> PlatformDataTable;

private:
    void InitializePlatforms();
};
