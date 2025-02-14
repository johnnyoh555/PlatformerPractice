// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/PFShakingPlatform.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

APFShakingPlatform::APFShakingPlatform()
{
    PrimaryActorTick.bCanEverTick = false;

    // 트리거 박스 생성 및 설정
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);
    TriggerBox->SetBoxExtent(FVector(110.f, 110.f, 30.f)); // 크기 조정
    TriggerBox->SetCollisionProfileName("Trigger"); // 오버랩 감지
    TriggerBox->SetGenerateOverlapEvents(true);
}

void APFShakingPlatform::BeginPlay()
{
    Super::BeginPlay();
    InitialLocation = GetActorLocation();  // 원래 위치 저장
    InitialRotation = GetActorRotation();  // 원래 회전값 저장

    // 충돌 이벤트 등록
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APFShakingPlatform::OnOverlapBegin);
}

void APFShakingPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{   
    UE_LOG(LogTemp, Log, TEXT("Overlap Detected with: %s"), *OtherActor->GetName());
    ACharacter* Player = Cast<ACharacter>(OtherActor);
    if (Player && !bIsShaking)
    {
        bIsShaking = true;
        StartShaking();
    }
}

void APFShakingPlatform::StartShaking()
{
    UE_LOG(LogTemp, Log, TEXT("Platform is shaking!"));

    // 일정 시간 후 발판 추락
    GetWorld()->GetTimerManager().SetTimer(DropTimerHandle, this, &APFShakingPlatform::DropPlatform, DropDelay, false);

    // 흔들리는 효과 (사인 곡선 기반 회전 적용)
    GetWorld()->GetTimerManager().SetTimer(ShakeTimerHandle, [this]()
    {
        float ShakeAmount = FMath::Sin(GetWorld()->TimeSeconds * 10.0f) * 5.0f; // 좌우 흔들림
        SetActorRotation(InitialRotation + FRotator(0, 0, ShakeAmount));
    }, 0.05f, true);  // 0.05초 간격으로 계속 호출 (애니메이션 느낌)
}

void APFShakingPlatform::DropPlatform()
{
    UE_LOG(LogTemp, Log, TEXT("Platform is falling!"));

    // 흔들림 멈추기
    GetWorld()->GetTimerManager().ClearTimer(ShakeTimerHandle);
    SetActorRotation(InitialRotation); // 원래 회전값으로 초기화

    // 물리 적용하여 발판 떨어지게 만들기
    PlatformMesh->SetSimulatePhysics(true);
    PlatformMesh->SetEnableGravity(true);

    // 일정 시간 후 다시 생성
    GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &APFShakingPlatform::RespawnPlatform, RespawnTime, false);
}

void APFShakingPlatform::RespawnPlatform()
{
    UE_LOG(LogTemp, Log, TEXT("Platform is respawning!"));

    // 발판을 원래 위치로 복원
    SetActorLocation(InitialLocation);
    SetActorRotation(InitialRotation);

    // 물리 해제하여 다시 고정
    PlatformMesh->SetSimulatePhysics(false);
    PlatformMesh->SetEnableGravity(false);

    bIsShaking = false; // 다시 발판을 활성화 가능하게 변경
}