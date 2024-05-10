// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Terrain/MT_FloorTerrain.h"
#include "MechanicsTestGameMode.generated.h"

UCLASS(minimalapi)
class AMechanicsTestGameMode : public AGameModeBase {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category="Terrain Generacion")
	int NumberOfTiles;
	
private:
	UPROPERTY()
	FTransform FloorAttachPoint;

public:
	TArray<AMT_FloorTerrain*> FloorTiles;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Classes)
	TSubclassOf<AMT_FloorTerrain> FloorClass;
	
public:
	AMechanicsTestGameMode();

	UFUNCTION()
	void AddFloor();

	UFUNCTION()
	void ExtendFloor();

protected:
	/** Called when the game starts */
	virtual void BeginPlay() override;
};





