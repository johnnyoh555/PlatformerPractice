// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PFCoinActor.generated.h"

UCLASS()
class PLATFORMERPRACTICE_API APFCoinActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APFCoinActor();

protected:
	UPROPERTY(VisibleAnywhere, Category = Coin)
	TObjectPtr<class UBoxComponent> Trigger;

	UPROPERTY(VisibleAnywhere, Category = Coin)
	TObjectPtr<class UStaticMeshComponent> Body;

	UPROPERTY(VisibleAnywhere, Category = Coin)
	TObjectPtr<class UStaticMeshComponent> Effect;

	UPROPERTY(VisibleAnywhere, Category = Sound)
	TObjectPtr<class USoundBase> PickupSound;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

};
