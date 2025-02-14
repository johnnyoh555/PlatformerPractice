// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
//#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Prop/PFHoverPlatformBase.h"
#include "PFHoverPatrolPlatform.generated.h"

UCLASS()
class PLATFORMERPRACTICE_API APFHoverPatrolPlatform : public APFHoverPlatformBase
{
    GENERATED_BODY()

    public:
    APFHoverPatrolPlatform();

protected:
    virtual void MovePlatform();
    //void BeginPlay() override;

    //void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    //    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    //    const FHitResult& SweepResult);

    //void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    //    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    //UPROPERTY()
    //TArray<AActor*> OverlappingActors; // 발판 위에 있는 캐릭터 목록

public:
    UPROPERTY(EditAnywhere, Category = "HoverPlatform|Patrol")
    TArray<FVector> PatrolPoints;

    UPROPERTY(EditAnywhere, Category = "HoverPlatform|Patrol")
    bool bLoop;

    void InitializePathFromData(const TArray<FVector>& AdditionalPoints);

private:
    int32 CurrentTargetIndex;
    bool bReversing;
    FTimerHandle MovementTimerHandle;

    void StartMovement();
};