// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/PFCharacterStatComponent.h"
#include "Item/PFPortalActor.h"
#include "EngineUtils.h"

// Sets default values for this component's properties
UPFCharacterStatComponent::UPFCharacterStatComponent()
{
	CurrentCoin = 0;

	// 객체의 초기화 순서 기억하기
	bWantsInitializeComponent = true;
}

void UPFCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	CurrentCoin = 0;
}

void UPFCharacterStatComponent::AddCoin()
{
    CurrentCoin++;
    OnCoinChanged.Broadcast(CurrentCoin, TotalCoin);
    if (CurrentCoin >= TotalCoin)
    {
        CheckCoinsAndActivatePortal();
    }
}

void UPFCharacterStatComponent::CheckCoinsAndActivatePortal()
{
    // 맵에 있는 포탈을 찾아서 활성화
    for (TActorIterator<APFPortalActor> It(GetWorld()); It; ++It)
    {
        APFPortalActor* Portal = *It;
        if (Portal)
        {
            Portal->ActivatePortal();
        }
    }
}