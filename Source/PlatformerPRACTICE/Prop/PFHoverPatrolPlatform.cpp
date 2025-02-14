// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/PFHoverPatrolPlatform.h"
#include "DrawDebugHelpers.h"


APFHoverPatrolPlatform::APFHoverPatrolPlatform()
{
    CurrentTargetIndex = 0;
    bReversing = false;
    bLoop = true;
}

//void APFHoverPatrolPlatform::BeginPlay()
//{
//    Super::BeginPlay();
//
//    PlatformMesh->OnComponentBeginOverlap.AddDynamic(this, &APFHoverPatrolPlatform::OnOverlapBegin);
//    PlatformMesh->OnComponentEndOverlap.AddDynamic(this, &APFHoverPatrolPlatform::OnOverlapEnd);
//}
//
//void APFHoverPatrolPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
//    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
//    const FHitResult& SweepResult)
//{
//    OverlappingActors.Add(OtherActor);
//}
//
//void APFHoverPatrolPlatform::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
//    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//    OverlappingActors.Remove(OtherActor);
//}

void APFHoverPatrolPlatform::InitializePathFromData(const TArray<FVector>& AdditionalPoints)
{
    if (AdditionalPoints.Num() > 0)
    {
        PatrolPoints.Add(GetActorLocation());
        PatrolPoints.Append(AdditionalPoints);
        UE_LOG(LogTemp, Log, TEXT("Add Points"));
        StartMovement();
    }
}

void APFHoverPatrolPlatform::StartMovement()
{
    if (PatrolPoints.Num() < 2) 
    {
        UE_LOG(LogTemp, Log, TEXT("Notenough points"));
        return;
    }
    UE_LOG(LogTemp, Log, TEXT("Start Platform Moving"));

    GetWorld()->GetTimerManager().SetTimer(
        MovementTimerHandle,
        this,
        &APFHoverPatrolPlatform::MovePlatform,
        0.01f, // 0.01초마다 업데이트
        true,
        DelayBeforeStart
    );
}

void APFHoverPatrolPlatform::MovePlatform()
{
    if (PatrolPoints.Num() < 2) return;

    FVector CurrentTarget = PatrolPoints[CurrentTargetIndex];
    FVector CurrentLocation = GetActorLocation();
    FVector Direction = (CurrentTarget - CurrentLocation).GetSafeNormal();
    FVector NewLocation = CurrentLocation + Direction * Speed * 0.01f;

    SetActorLocation(NewLocation);

    //// 발판 위의 캐릭터 이동
    //for (AActor* Actor : OverlappingActors)
    //{
    //    ACharacter* Character = Cast<ACharacter>(Actor);
    //    if (Character)
    //    {
    //        FVector Offset = NewLocation - CurrentLocation;
    //        Character->AddActorWorldOffset(Offset);
    //    }
    //}

    if (FVector::Dist(NewLocation, CurrentTarget) < 10.0f)
    {
        if (bReversing)
        {
            CurrentTargetIndex--;
            if (CurrentTargetIndex < 0)
            {
                if (bLoop)
                {
                    CurrentTargetIndex = 1;
                    bReversing = false;
                }
                else
                {
                    CurrentTargetIndex = 0;
                }
            }
        }
        else
        {
            CurrentTargetIndex++;
            if (CurrentTargetIndex >= PatrolPoints.Num())
            {
                if (bLoop)
                {
                    CurrentTargetIndex = PatrolPoints.Num() - 2;
                    bReversing = true;
                }
                else
                {
                    CurrentTargetIndex = PatrolPoints.Num() - 1;
                }
            }
        }
    }
}