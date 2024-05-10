// Fill out your copyright notice in the Description page of Project Settings.


#include "Terrain/MT_Obstacle.h"

// Sets default values
float AMT_Obstacle::MinScale = 0.7f;
float AMT_Obstacle::MaxScale = 15.f;
AMT_Obstacle::AMT_Obstacle() {
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	RootComponent = MeshComponent;
}

void AMT_Obstacle::BeginPlay() {
	Super::BeginPlay();
	MeshComponent->SetWorldScale3D(FVector(2, 2, FMath::RandRange(MinScale, MaxScale)));
}



