// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ManaBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class CAPTUREBUCKET_API UManaBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UManaBarWidget(const FObjectInitializer& ObjectInitializer);

	void UpdateManaBar(float Percentage);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UProgressBar* progress_bar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* text;
private:
	void SetText(float Percentage);
};

