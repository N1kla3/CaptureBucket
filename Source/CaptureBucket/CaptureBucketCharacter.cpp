// Copyright Epic Games, Inc. All Rights Reserved.

#include "CaptureBucketCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "Engine/World.h"

ACaptureBucketCharacter::ACaptureBucketCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	m_CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	m_CameraBoom->SetupAttachment(RootComponent);
	m_CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	m_CameraBoom->TargetArmLength = 800.f;
	m_CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	m_CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	m_TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	m_TopDownCameraComponent->SetupAttachment(m_CameraBoom, USpringArmComponent::SocketName);
	m_TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	m_CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	m_CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		m_CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	m_CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	m_CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ACaptureBucketCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_FullHealth = 1000.f;
	m_Health = m_FullHealth;
	m_HealthPercentage = 1.f;
	m_PreviousHealth = m_HealthPercentage;
	SetCanBeDamaged(true);

	m_FullMagic = 100.f;
	m_Magic = m_FullMagic;
	m_MagicPercentage = 1.f;
	m_PreviousMagic = m_MagicPercentage;
	bCanUseMagic = true;

	if (m_MagicCurve)
	{
		FOnTimelineFloat timeline_callback;
		FOnTimelineEventStatic timeline_finished_callback;
		timeline_callback.BindUFunction(this, FName("SetMagicValue"));
		timeline_finished_callback.BindUFunction(this, FName("SetMagicState"));
		m_MyTimeline.AddInterpFloat(m_MagicCurve, timeline_callback);
		m_MyTimeline.SetTimelineFinishedFunc(timeline_finished_callback);
	}
}


void ACaptureBucketCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (m_CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = m_TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = m_TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				m_CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			m_CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			m_CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}

float ACaptureBucketCharacter::GetHealth() const
{
	return m_HealthPercentage;
}

float ACaptureBucketCharacter::GetMagic() const
{
	return m_MagicPercentage;
}

void ACaptureBucketCharacter::UpdateHealth(float HealthChange)
{
	
}

void ACaptureBucketCharacter::UpdateMagic(float MagicChange)
{
	
}

FText ACaptureBucketCharacter::GetHealthIntText() const
{
	int hp = FMath::RoundHalfFromZero(m_HealthPercentage * 100);
	FString hp_string = FString::FromInt(hp);
	FString health_hud = hp_string + FString(TEXT("%"));
	FText result = FText::FromString(health_hud);
	return result;
}

FText ACaptureBucketCharacter::GetMagicIntText() const
{
	int magic = FMath::RoundHalfFromZero(m_MagicPercentage * 100);
	FString magic_string = FString::FromInt(magic);
	FString magic_hud = magic_string + FString(TEXT("%"));
	FText result = FText::FromString(magic_hud);
	return result;
}

void ACaptureBucketCharacter::DamageTimer()
{
}

void ACaptureBucketCharacter::SetDamageState()
{
}

void ACaptureBucketCharacter::SetMagicValue()
{
}

void ACaptureBucketCharacter::SetMagicState()
{
}

void ACaptureBucketCharacter::SetMagicChange(float MagicChange)
{
}

bool ACaptureBucketCharacter::PlayFlash()
{
	return true;
}
