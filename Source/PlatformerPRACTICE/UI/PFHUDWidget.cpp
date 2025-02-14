// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PFHUDWidget.h"
#include "UI/PFCoinHUDWidget.h"
#include "CharacterStat/PFCharacterStatComponent.h"

UPFHUDWidget::UPFHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UPFHUDWidget::UpdateCoin(float CurrentCoin, float TotalCoin)
{
    if (CoinHUD)
    {
    UE_LOG(LogTemp, Log, TEXT("Try To UpdateCoin"));
        CoinHUD->UpdateCoinDisplay(CurrentCoin, TotalCoin); // CoinHUD 위젯의 업데이트 함수 호출
    }
}

void UPFHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CoinHUD = Cast<UPFCoinHUDWidget>(GetWidgetFromName(TEXT("CoinWidget")));
	ensure(CoinHUD);

	// 디스플레이를 소유하는 컨트롤러도 가져올 수 있고 바로 빙의한 폰을 가져올 수도 있다.
    // Owning PlayerPawn에서 StatComponent 가져오기
    APawn* OwningPawn = GetOwningPlayerPawn();
    if (OwningPawn)
    {
        UPFCharacterStatComponent* StatComponent = OwningPawn->FindComponentByClass<UPFCharacterStatComponent>();
        if (StatComponent)
        {
            // OnCoinChanged 델리게이트에 UpdateCoin 바인딩
            StatComponent->OnCoinChanged.AddUObject(this, &UPFHUDWidget::UpdateCoin);
            StatComponent->OnCoinChanged.Broadcast(StatComponent->GetCurrentCoin(), StatComponent->GetTotalCoin());
            UE_LOG(LogTemp, Log, TEXT("Added UpdateCoin"))
        }
    }
}
