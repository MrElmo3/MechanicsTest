// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "MT_TerrainGenerator.generated.h"

UCLASS()
class MECHANICSTEST_API AMT_TerrainGenerator : public AActor {
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Terrain Generation", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* FloorDetectionColider = nullptr;

	// UPROPERTY(EditDefaultsOnly, Category="Spawned Item")
	// TSubclassOf<AActor> FloorToSpawn; 
	
public:
	// Sets default values for this actor's properties
	AMT_TerrainGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void GenerateFloor(
		class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
};
