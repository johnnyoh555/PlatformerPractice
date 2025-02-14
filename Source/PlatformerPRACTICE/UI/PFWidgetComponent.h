// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "PFWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERPRACTICE_API UPFWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
protected:
	virtual void InitWidget() override;
	
};
