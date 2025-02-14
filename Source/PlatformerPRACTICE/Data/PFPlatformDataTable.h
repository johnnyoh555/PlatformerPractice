#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" // FTableRowBase 포함
#include "PFPlatformDataTable.generated.h"

USTRUCT(BlueprintType)
struct FPFPlatformDataTable : public FTableRowBase
{
    GENERATED_BODY()

    // 발판 고유 ID
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform")
    FName PlatformID;

    // 시작 위치
  /*  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform")
    FVector StartLocation;*/

    // 경로 포인트들
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform")
    TArray<FVector> PathPoints;

    // 이동 속도
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform")
    float Speed;

    // 활성화 지연 시간
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform")
    float DelayBeforeStart;
};
