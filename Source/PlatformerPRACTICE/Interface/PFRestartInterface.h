// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PFRestartInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPFRestartInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PLATFORMERPRACTICE_API IPFRestartInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 스테이지를 리스타트하는 메서드
	virtual void RestartStage() = 0;
	virtual void RestartStageDelayed() = 0;
	FTimerHandle TimerHandle;
};
