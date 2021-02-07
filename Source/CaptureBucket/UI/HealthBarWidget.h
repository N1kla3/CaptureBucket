// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

/**
 *  
 */
UCLASS()
class CAPTUREBUCKET_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UHealthBarWidget(const FObjectInitializer& ObjectInitializer);

	void UpdateHealthBar(float Percentage);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UProgressBar* progress_bar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* text;

private:
	void ChangeText(float Percent);	
};
