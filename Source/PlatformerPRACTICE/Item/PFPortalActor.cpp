// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PFPortalActor.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Interface/PFPortalInteractableInterface.h"

// Sets default values
APFPortalActor::APFPortalActor()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
    Ring = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring"));
    PortalEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PortalEffect"));

    static  ConstructorHelpers::FObjectFinder<UStaticMesh> BodyMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/StackOBot/Environment/Props/SM_SpawnPad_Base.SM_SpawnPad_Base'"));
    if (BodyMeshRef.Object)
    {
        Body->SetStaticMesh(BodyMeshRef.Object);
    }

    static  ConstructorHelpers::FObjectFinder<UStaticMesh> RingMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/StackOBot/Environment/Props/SM_SpawnPad_Ring.SM_SpawnPad_Ring'"));
    if (RingMeshRef.Object)
    {
        Ring->SetStaticMesh(RingMeshRef.Object);
    }

    RootComponent = CollisionBox;

    PortalEffect->SetupAttachment(RootComponent);
    Body->SetupAttachment(RootComponent);
    Ring->SetupAttachment(RootComponent);
    CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionBox->SetCollisionResponseToAllChannels(ECR_Overlap);
    FVector CurrentExtent = CollisionBox->GetUnscaledBoxExtent(); // 현재 크기
    CollisionBox->SetBoxExtent(FVector(CurrentExtent.X * 0.5f, CurrentExtent.Y * 0.5f, CurrentExtent.Z * 1.f));

    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APFPortalActor::OnOverlapBegin);

    bIsActive = false; // 기본값으로 비활성화

    TargetMapName = FName("Step2");
}

void APFPortalActor::BeginPlay()
{
    Super::BeginPlay();

    // 이펙트 초기화

    LoadPortalEffect();
    // 초기 상태에서 이펙트를 비활성화
    if (PortalEffect)
    {
        UE_LOG(LogTemp, Log, TEXT("DeActivate"));
        PortalEffect->Deactivate();
    }
}

void APFPortalActor::LoadPortalEffect()
{
    FString AssetPath = TEXT("/Game/StackOBot/FX/SpawnPadActive/FX_SpawnPadActive.FX_SpawnPadActive");

    // StaticLoadObject를 사용하여 NiagaraSystem 로드
    UNiagaraSystem* NiagaraSystem = Cast<UNiagaraSystem>(StaticLoadObject(UNiagaraSystem::StaticClass(), nullptr, *AssetPath));

    if (NiagaraSystem)
    {
        PortalEffect->SetAsset(NiagaraSystem); // NiagaraSystem 설정
        UE_LOG(LogTemp, Log, TEXT("Successfully loaded Niagara effect."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load Niagara effect."));
    }
}

void APFPortalActor::ActivatePortal()
{
    bIsActive = true;
    if (PortalEffect)
    {
        PortalEffect->Activate(); // 이펙트 활성화
    }
}

void APFPortalActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (bIsActive && OtherActor && OtherActor->ActorHasTag(TEXT("Player"))) // 포탈 활성화 여부 확인
    {
        if (IPFPortalInteractableInterface* Interactable = Cast<IPFPortalInteractableInterface>(OtherActor))
        {
            Interactable->ShrinkBeforeTeleport(); // 인터페이스 함수 호출
        }

        if (!TargetMapName.IsNone())
        {
            //UGameplayStatics::OpenLevel(this, TargetMapName); // 맵 로드
        }
    }
}