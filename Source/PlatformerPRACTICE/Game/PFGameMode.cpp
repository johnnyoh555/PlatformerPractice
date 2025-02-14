// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PFGameMode.h"
#include "TimerManager.h"
#include "Item/PFCoinActor.h"
#include "CharacterStat/PFCharacterStatComponent.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

APFGameMode::APFGameMode()
{
	/*static ConstructorHelpers::FClassFinder<APawn> ThirdPersonClassRef(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C"));
	if (ThirdPersonClassRef.Class)
	{
		DefaultPawnClass = ThirdPersonClassRef.Class;
	}*/

	// Pawn 지정
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Script/PlatformerPRACTICE.PFCharacter"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
		UE_LOG(LogTemp, Log, TEXT("ASD"));
	}
	// 헤더 참조를 덜하기 위해서 직접 클래스 정보를 가져옴
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/PlatformerPRACTICE.PFPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
		UE_LOG(LogTemp, Log, TEXT("DDD"));
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> BGMRef(TEXT("/Script/MetasoundEngine.MetaSoundSource'/Game/StackOBot/Audio/SFX_Music.SFX_Music'"));
	if (BGMRef.Succeeded()) // FObjectFinder로 사운드 로드 성공 여부 확인
	{
		BGM = BGMRef.Object; // 로드된 사운드를 BGM 변수에 저장

		// BGM이 유효하다면 재생
		if (BGM)
		{
			UGameplayStatics::PlaySound2D(this, BGM, 0.5f); // 볼륨 50%
		}
	}
}

void APFGameMode::BeginPlay()
{
	Super::BeginPlay();

	// 플레이어의 CharacterStatComponent 가져오기
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!PlayerPawn) return;

	UPFCharacterStatComponent* StatComp = PlayerPawn->FindComponentByClass<UPFCharacterStatComponent>();
	if (StatComp)
	{
		int32 CoinCount = 0;

		// 현재 스테이지의 모든 코인 액터 찾기
		for (TActorIterator<APFCoinActor> It(GetWorld()); It; ++It)
		{
			CoinCount++;
		}

		StatComp->SetTotalCoin(CoinCount);

		UE_LOG(LogTemp, Log, TEXT("Total Coins in this stage: %d"), CoinCount);
	}
}

void APFGameMode::RestartStage()
{
	// 타이머 설정으로 10초 후에 RestartStageDelayed 실행
	GetWorldTimerManager().SetTimer(
		TimerHandle,                               // 타이머 핸들
		this,                                     // 실행 대상
		&APFGameMode::RestartStageDelayed,        // 실행할 함수
		3.0f,                                    // 딜레이 시간 (초)
		false                                     // 반복 여부 (false = 1회 실행)
	);
}

void APFGameMode::RestartStageDelayed()
{
	// 현재 레벨 이름 가져오기
	FString CurrentLevelName = GetWorld()->GetName();

	// 레벨 다시 로드
	UGameplayStatics::OpenLevel(this, FName(*CurrentLevelName), false);

	UE_LOG(LogTemp, Log, TEXT("Stage restarted: %s"), *CurrentLevelName);
}