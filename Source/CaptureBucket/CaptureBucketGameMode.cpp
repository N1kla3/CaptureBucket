// Copyright Epic Games, Inc. All Rights Reserved.

#include "CaptureBucketGameMode.h"
#include "CaptureBucketPlayerController.h"
#include "CaptureBucketCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACaptureBucketGameMode::ACaptureBucketGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ACaptureBucketPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}