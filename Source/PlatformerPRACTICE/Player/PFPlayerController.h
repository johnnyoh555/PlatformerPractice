// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PFPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERPRACTICE_API APFPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APFPlayerController();
	
protected:
	virtual void BeginPlay() override;
	
	//HUD Section
protected:
	UPROPERTY(EditAnywhere,	BlueprintReadWrite, Category = HUD)
	TSubclassOf<class UPFHUDWidget> PFHUDWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HUD)
	TObjectPtr<class UPFHUDWidget> PFHUDWidget;
};
