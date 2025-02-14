// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interface/PFRestartInterface.h"
#include "PFGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERPRACTICE_API APFGameMode : public AGameModeBase, public IPFRestartInterface
{
	GENERATED_BODY()
	
public:
	APFGameMode();

private:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Sound)
	TObjectPtr<class USoundBase> BGM;

public:
	// 인터페이스 메서드 구현
	virtual void RestartStage() override;
	virtual void RestartStageDelayed() override;
};
