// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PFPlayerController.h"
#include "UI/PFHUDWidget.h"

APFPlayerController::APFPlayerController()
{
	static ConstructorHelpers::FClassFinder<UPFHUDWidget> PFHUDWidgetRef(TEXT("/Game/PF/UI/WBP_PFHUD.WBP_PFHUD_C"));
	if (PFHUDWidgetRef.Class)
	{
		PFHUDWidgetClass = PFHUDWidgetRef.Class;
	}
}

void APFPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 게임이 시작하자 마자 뷰포트로 포인터가 이동
	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);

	PFHUDWidget = CreateWidget<UPFHUDWidget>(this, PFHUDWidgetClass);
	if (PFHUDWidget)
	{
		PFHUDWidget->AddToViewport();
	}
}
