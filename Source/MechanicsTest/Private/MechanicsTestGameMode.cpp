// Copyright Epic Games, Inc. All Rights Reserved.

#include "MechanicsTest/Public/MechanicsTestGameMode.h"
#include "MechanicsTest/Public/MechanicsTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMechanicsTestGameMode::AMechanicsTestGameMode()
	: Super(){
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(
		TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
