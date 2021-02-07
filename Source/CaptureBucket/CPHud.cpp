// Fill out your copyright notice in the Description page of Project Settings.


#include "CPHud.h"

#include "CaptureBucket.h"
#include "CaptureBucketPlayerController.h"
#include "Blueprint/UserWidget.h"

ACPHud::ACPHud()
{
}

void ACPHud::BeginPlay()
{
	Super::BeginPlay();
}

void ACPHud::Tick(float DeltaSeconds)
{
}

void ACPHud::DrawHUD()
{
	Super::DrawHUD();
}

void ACPHud::SetupHUD(ACaptureBucketPlayerController* controller)
{
	if (!controller)
	{
		UE_LOG(UILog, Warning, TEXT("No Controller in ACPHud"));
		return;
	}
	if (!controller->IsLocalController())
	{
		UE_LOG(UILog, Warning, TEXT("ACPHud:: controller is not local"));
		return;
	}

	if (root_canvas_class)
	{
		m_RootCanvas = CreateWidget<UUserWidget>(controller, root_canvas_class);
		m_RootCanvas->AddToViewport(0);
	}
}
