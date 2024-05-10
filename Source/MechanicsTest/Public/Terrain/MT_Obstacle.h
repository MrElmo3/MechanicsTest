// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MT_Obstacle.generated.h"

UCLASS()
class MECHANICSTEST_API AMT_Obstacle : public AActor {
	GENERATED_BODY()
	
	static float MinScale;
	
	static float MaxScale;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

public:
	// Sets default values for this actor's properties
	AMT_Obstacle();

protected:
	virtual void BeginPlay() override;
};
