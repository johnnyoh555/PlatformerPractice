// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PFWidgetComponent.h"
#include "PFUserWidget.h"

void UPFWidgetComponent::InitWidget()
{
	Super::InitWidget();

	UPFUserWidget* PFUserWidget = Cast<UPFUserWidget>(GetWidget());
	if (PFUserWidget)
	{
		PFUserWidget->SetOwningActor(GetOwner());
	}
}
