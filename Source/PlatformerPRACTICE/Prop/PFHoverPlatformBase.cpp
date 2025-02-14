// Fill out your copyright notice in the Description page of Project Settings.


#include "PFHoverPlatformBase.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"


APFHoverPlatformBase::APFHoverPlatformBase()
{
    bIsActive = false;
    Speed = 100.0f;

    // 매쉬 컴포넌트 생성
    PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
    RootComponent = PlatformMesh;

    // 기본 매쉬 설정
    static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Script/Engine.StaticMesh'/Game/StackOBot/Environment/Modular/SM_Modules_Floor.SM_Modules_Floor'"));
    if (DefaultMesh.Succeeded())
    {
        PlatformMesh->SetStaticMesh(DefaultMesh.Object);
    }
}

void APFHoverPlatformBase::BeginPlay()
{
    Super::BeginPlay();
    StartLocation = GetActorLocation();
}

void APFHoverPlatformBase::ActivatePlatform()
{
    bIsActive = true;
}

void APFHoverPlatformBase::DeactivatePlatform()
{
    bIsActive = false;
}
