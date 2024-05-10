// Copyright Epic Games, Inc. All Rights Reserved.

#include "MechanicsTest/Public/MechanicsTestGameMode.h"

#include "Algo/ForEach.h"
#include "MechanicsTest/Public/MechanicsTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMechanicsTestGameMode::AMechanicsTestGameMode()
	: Super(){
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(
		TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	static ConstructorHelpers::FClassFinder<AActor> FloorClassFinder(
		TEXT("/Game/Runner/Blueprints/Terrain/BP_FloorTerrain"));
	FloorClass = FloorClassFinder.Class;

	NumberOfTiles = 15;
	
}

void AMechanicsTestGameMode::BeginPlay() {
	Super::BeginPlay();
	for (int i = 0; i < NumberOfTiles; i++) {
		AddFloor();
	}
}


void AMechanicsTestGameMode::AddFloor() {
	AMT_FloorTerrain* floor = GetWorld()->SpawnActor<AMT_FloorTerrain>(FloorClass, FloorAttachPoint);
	FloorAttachPoint = floor->GetAttachPoint();
	FloorTiles.Add(floor);
}

void AMechanicsTestGameMode::ExtendFloor() {
	AddFloor();
	if(FloorTiles.Num() > NumberOfTiles + 2) {
		AMT_FloorTerrain* floor = FloorTiles[0];
		floor->Destroy();
		FloorTiles.RemoveAt(0);
	}
}


