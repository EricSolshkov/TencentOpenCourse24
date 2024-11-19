// Copyright Epic Games, Inc. All Rights Reserved.

#include "Test54GameMode.h"
#include "Test54Character.h"
#include "UObject/ConstructorHelpers.h"

ATest54GameMode::ATest54GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
