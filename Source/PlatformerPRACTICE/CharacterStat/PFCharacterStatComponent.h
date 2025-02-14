// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "UObject/ScriptDelegates.h"
#include "Components/ActorComponent.h"
#include "PFCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCoinChangedDelegates, float /*NewCoinValue*/, float /*TotalCoinValue*/);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATFORMERPRACTICE_API UPFCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPFCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void InitializeComponent() override;

public:
	FOnCoinChangedDelegates OnCoinChanged;

	FORCEINLINE float GetCurrentCoin() const { return CurrentCoin; }
	FORCEINLINE float GetTotalCoin() const { return TotalCoin; }
	void AddCoin();
	FORCEINLINE void SetTotalCoin(int32 Coin)
	{ 
		TotalCoin = (float)Coin;
		OnCoinChanged.Broadcast(CurrentCoin, TotalCoin);
	}

protected:
	UPROPERTY(Transient, VisibleAnywhere, Category = Coins)
	float CurrentCoin;

	UPROPERTY(Transient, VisibleAnywhere, Category = Coins)
	float TotalCoin;

	void CheckCoinsAndActivatePortal();

};
