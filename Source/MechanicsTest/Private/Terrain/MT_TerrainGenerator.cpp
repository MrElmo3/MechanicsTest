// Fill out your copyright notice in the Description page of Project Settings.


#include "Terrain/MT_TerrainGenerator.h"


// Sets default values
AMT_TerrainGenerator::AMT_TerrainGenerator() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloorDetectionColider = CreateDefaultSubobject<UBoxComponent>(FName("Detection Collider"));
	SetRootComponent(FloorDetectionColider);

	FloorDetectionColider->InitBoxExtent(FVector(250,125,12.5f));

	// static ConstructorHelpers::FClassFinder<APawn> AssetFile(
	// 	TEXT("/Game/Runner/Blueprints/Terrain/BP_TerrainGenerator"));
	// FloorToSpawn = AssetFile.Class;
	
}

void AMT_TerrainGenerator::BeginPlay() {
	Super::BeginPlay();
	FloorDetectionColider->OnComponentEndOverlap.AddDynamic(this, &AMT_TerrainGenerator::GenerateFloor);
}

void AMT_TerrainGenerator::GenerateFloor(
	class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex) {

	// GetWorld()->SpawnActor(FloorToSpawn, new FVector(3000.f, 0.f, 0.f));
}


