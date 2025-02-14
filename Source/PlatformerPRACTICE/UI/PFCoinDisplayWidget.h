// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PFUserWidget.h"
#include "PFCoinDisplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERPRACTICE_API UPFCoinDisplayWidget : public UPFUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPFCoinDisplayWidget(const FObjectInitializer& ObjectInitializer);
	void UpdateCoinScore(float NewCoinScore, float TotalCoin);

protected:
	UPROPERTY()
	
	TObjectPtr<class UEditableTextBox> CoinTextBox;
};
