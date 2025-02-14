// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PFCoinDisplayWidget.h"
#include "Components/EditableTextBox.h"
#include "Interface/PFCharacterWidgetInterface.h"

UPFCoinDisplayWidget::UPFCoinDisplayWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UPFCoinDisplayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CoinTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("CoinText")));
	ensure(CoinTextBox);

	IPFCharacterWidgetInterface* CharacterWidget = Cast<IPFCharacterWidgetInterface>(OwningActor);
	if (CharacterWidget)
	{
		CharacterWidget->SetupCharacterWidget(this);
	}
}

void UPFCoinDisplayWidget::UpdateCoinScore(float NewCoinScore, float TotalCoin)
{
	if (CoinTextBox)
	{
		UE_LOG(LogTemp, Log, TEXT("[PFCoinDisplayWidget] UI Updated: New Coin Score = %f"), NewCoinScore);
		CoinTextBox->SetText(FText::FromString(FString::Printf(TEXT("Coins: %d"), static_cast<int32>(NewCoinScore))));
	}
}
