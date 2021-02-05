// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

UHealthBarWidget::UHealthBarWidget(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	
}

void UHealthBarWidget::UpdateHealthBar(float Percentage)
{
	progress_bar->SetPercent(Percentage);
	ChangeText(Percentage);
}

void UHealthBarWidget::ChangeText(float Percent)
{
	text->SetText(FText::FromString(FString::Printf(TEXT("%f %%"), Percent * 100)));
}
