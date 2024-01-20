// Copyright Epic Games, Inc. All Rights Reserved.

#include "SandstormGameMode.h"
#include "SandstormCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASandstormGameMode::ASandstormGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
