// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PFCoinActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Interface/PFCharacterCoinInterface.h"

// Sets default values
APFCoinActor::APFCoinActor()
{
    Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinBody"));
    Effect = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinEffect"));

    RootComponent = Trigger;
    Body->SetupAttachment(Trigger);
    Effect->SetupAttachment(Trigger);

    Trigger->SetCollisionProfileName(TEXT("PFTrigger"));
    FVector CurrentExtent = Trigger->GetUnscaledBoxExtent(); // 현재 크기
    Trigger->SetBoxExtent(CurrentExtent * 0.7f); // 70%로 축소
    Trigger->OnComponentBeginOverlap.AddDynamic(this, &APFCoinActor::OnOverlapBegin);

    static  ConstructorHelpers::FObjectFinder<UStaticMesh> BodyMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/PF/Character/SM_GenericPlayerPickup_Core1.SM_GenericPlayerPickup_Core1'"));
    if (BodyMeshRef.Object)
    {
        Body->SetStaticMesh(BodyMeshRef.Object);
    }

    static  ConstructorHelpers::FObjectFinder<UStaticMesh> EffectMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/PF/Character/SM_GenericPlayerPickup_Ring1.SM_GenericPlayerPickup_Ring1'"));
    if (EffectMeshRef.Object)
    {
        Effect->SetStaticMesh(EffectMeshRef.Object);
    }
    /*Mesh->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));*/
    Body->SetCollisionProfileName(TEXT("NoCollision"));
    Effect->SetCollisionProfileName(TEXT("NoCollision"));

    static ConstructorHelpers::FObjectFinder<USoundBase> SoundRef(TEXT("/Game/StackOBot/Audio/SFX_CollectCoin.SFX_CollectCoin"));
    if (SoundRef.Succeeded())
    {
        PickupSound = SoundRef.Object;
    }
}

void APFCoinActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
    IPFCharacterCoinInterface* OverlappingPawn = Cast<IPFCharacterCoinInterface>(OtherActor);
    if (OverlappingPawn)
    {
        UE_LOG(LogTemp, Log, TEXT("Coin!!!!!!"));
        OverlappingPawn->TakeCoin();
    }

    if (PickupSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation(), 0.5f);
    }

    Body->SetHiddenInGame(true);
    Effect->SetHiddenInGame(true);
    SetActorEnableCollision(false);

    GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
    {
        Destroy();
    });
}

