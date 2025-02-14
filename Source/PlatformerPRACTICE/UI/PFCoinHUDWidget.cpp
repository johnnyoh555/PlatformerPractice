// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PFCoinHUDWidget.h"

void UPFCoinHUDWidget::UpdateCoinDisplay(float InCurrentCoin, float InTotalCoin)
{
    CurrentCoin->SetText(FText::AsNumber(InCurrentCoin));
    TotalCoin->SetText(FText::AsNumber(InTotalCoin));
    CurrentState->SetText(InCurrentCoin == InTotalCoin ? FText::FromString(TEXT("Ready")) : FText::FromString(TEXT("Not Ready")));
    UE_LOG(LogTemp, Log, TEXT("Updated HUD"))
}
