// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PFCoinHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERPRACTICE_API UPFCoinHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

    // 텍스트 블록에 대한 포인터 선언
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> CurrentCoin;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> TotalCoin;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> CurrentState;

public:
	void UpdateCoinDisplay(float CurrentCoin, float TotalCoin);

};
