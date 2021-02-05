// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CPHud.generated.h"

/**
 * 
 */
UCLASS()
class CAPTUREBUCKET_API ACPHud : public AHUD
{
	GENERATED_BODY()
public:
	ACPHud();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void DrawHUD() override;

	void SetupHUD(class ACaptureBucketPlayerController* controller);

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> root_canvas_class;

private:
	UPROPERTY()
	UUserWidget* m_RootCanvas;
	
};
