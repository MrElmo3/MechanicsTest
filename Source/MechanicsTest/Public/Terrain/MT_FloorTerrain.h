// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MT_Obstacle.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "MT_FloorTerrain.generated.h"

UCLASS()
class MECHANICSTEST_API AMT_FloorTerrain : public AActor {
	GENERATED_BODY()

	UPROPERTY()
	USceneComponent* CustomRootComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ArrowComponent;
	
	UPROPERTY()
	TArray<float> LanePosition = {-325.f, 0.f, 325.f};

	UPROPERTY()
	TArray<FVector> ObstacleSpawnLocation;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Classes)
	TSubclassOf<AMT_Obstacle> ObstacleClass;

public:
	// Sets default values for this pawn's properties
	AMT_FloorTerrain();

private:

	UFUNCTION()
	void SetupObstacles();


protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnBoxBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep, const
		FHitResult& SweepResult);

public:
	UFUNCTION()
	FTransform GetAttachPoint() const { return ArrowComponent->GetComponentTransform(); }

};


