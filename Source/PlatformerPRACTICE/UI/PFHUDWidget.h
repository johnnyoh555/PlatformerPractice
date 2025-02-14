// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PFHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERPRACTICE_API UPFHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPFHUDWidget(const FObjectInitializer& ObjectInitializer);

public:
	void UpdateCoin(float CurrentCoin, float TotalCoin);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
	TObjectPtr<class UPFCoinHUDWidget> CoinHUD;
};
