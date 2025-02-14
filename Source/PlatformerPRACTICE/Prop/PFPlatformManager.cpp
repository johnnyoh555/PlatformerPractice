// Fill out your copyright notice in the Description page of Project Settings.


#include "PFPlatformManager.h"
//#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
#include "PFHoverPatrolPlatform.h"
#include "Data/PFPlatformDataTable.h"

APFPlatformManager::APFPlatformManager()
{
    PrimaryActorTick.bCanEverTick = false; // Tick 불필요

    // 데이터 테이블 초기화
    static ConstructorHelpers::FObjectFinder<UDataTable> DataTableAsset(TEXT("/Game/PF/Data/PFPlatformDataTable.PFPlatformDataTable"));
    if (DataTableAsset.Succeeded())
    {
        PlatformDataTable = DataTableAsset.Object;
        UE_LOG(LogTemp, Log, TEXT("Platform Data Table loaded successfully in constructor."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Platform Data Table in constructor."));
    }
}

void APFPlatformManager::BeginPlay()
{
    Super::BeginPlay();

    InitializePlatforms();
}

void APFPlatformManager::InitializePlatforms()
{
    if (!PlatformDataTable)
    {
        UE_LOG(LogTemp, Warning, TEXT("Platform Data Table is not set!"));
        return;
    }

    static const FString ContextString(TEXT("Platform Data Context"));
    TArray<FPFPlatformDataTable*> Rows;
    PlatformDataTable->GetAllRows<FPFPlatformDataTable>(ContextString, Rows);

    for (const FPFPlatformDataTable* Row : Rows)
    {
        if (!Row) continue;

        // 월드에 배치된 발판을 찾아서 데이터 적용
        TArray<AActor*> FoundPlatforms;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), APFHoverPatrolPlatform::StaticClass(), FoundPlatforms);

        for (AActor* FoundActor : FoundPlatforms)
        {
            APFHoverPatrolPlatform* Platform = Cast<APFHoverPatrolPlatform>(FoundActor);
            if (Platform && Platform->ActorHasTag(Row->PlatformID)) // 태그를 이용해 매칭
            {
                Platform->Speed = Row->Speed;
                Platform->DelayBeforeStart = Row->DelayBeforeStart;
                Platform->InitializePathFromData(Row->PathPoints);
                UE_LOG(LogTemp, Log, TEXT("Platform found and initialized: %s"), *Row->PlatformID.ToString());
            }
        }
    }
}
