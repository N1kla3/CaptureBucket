// Copyright Epic Games, Inc. All Rights Reserved.

#include "CaptureBucketPlayerController.h"

#include "CaptureBucket.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "CaptureBucketCharacter.h"
#include "CPHud.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"

ACaptureBucketPlayerController::ACaptureBucketPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ACaptureBucketPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() == ROLE_Authority)
	{
		if (const auto controller = GetWorld()->GetFirstPlayerController<ACaptureBucketPlayerController>())
		{
			if (controller == this)
			{
				SetupHUD();
			}
		}
	}
	else
	{
		SetupHUD();
	}
	if (GetPawn())
   	{
   		m_Destination = GetPawn()->GetActorLocation();
   	}
}

void ACaptureBucketPlayerController::SetupHUD()
{
	if (!HUDClass)
	{
		UE_LOG(LogCaptureBucket, Error, TEXT("Controller:: no HUD class"));
		Destroy();
		return;
	}

	FActorSpawnParameters param;
	param.Owner = this;
	param.Instigator = this->GetInstigator();
	param.ObjectFlags |= RF_Transient;

	MyHUD = GetWorld()->SpawnActor<AHUD>(HUDClass, param);

	auto capture_bucket_hud = Cast<ACPHud>(MyHUD);
	if (capture_bucket_hud)
	{
		capture_bucket_hud->SetupHUD(this);	
	}
	else
	{
		UE_LOG(LogCaptureBucket, Warning, TEXT("Controller:: !setupHUD"));
	}
}

void ACaptureBucketPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
	SetNewMoveDestination(m_Destination);
}

void ACaptureBucketPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ACaptureBucketPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ACaptureBucketPlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ACaptureBucketPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ACaptureBucketPlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &ACaptureBucketPlayerController::OnResetVR);
}

void ACaptureBucketPlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ACaptureBucketPlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (ACaptureBucketCharacter* MyPawn = Cast<ACaptureBucketCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			m_Destination = Hit.ImpactPoint;
		}
	}
}

void ACaptureBucketPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ACaptureBucketPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		if (Distance > 5.f)
		{
			MyPawn->AddMovementInput(UKismetMathLibrary::GetDirectionUnitVector(MyPawn->GetActorLocation(), DestLocation));
		}
	}
}

void ACaptureBucketPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ACaptureBucketPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}
