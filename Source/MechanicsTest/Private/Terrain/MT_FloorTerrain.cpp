// Fill out your copyright notice in the Description page of Project Settings.


#include "Terrain/MT_FloorTerrain.h"

#include "MechanicsTestCharacter.h"
#include "MechanicsTestGameMode.h"


// Sets default values
AMT_FloorTerrain::AMT_FloorTerrain() {

	static ConstructorHelpers::FClassFinder<AActor> ObstacleClassFinder(
		TEXT("/Game/Runner/Blueprints/Terrain/BP_Obstacle"));
	ObstacleClass = ObstacleClassFinder.Class;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(CustomRootComponent);
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	MeshComponent->SetupAttachment(CustomRootComponent);
	MeshComponent->SetRelativeScale3D(FVector(10.f, 20.f, 0.5f));
	MeshComponent->SetEnableGravity(false);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("Generation Colision"));
	BoxComponent->SetupAttachment(CustomRootComponent);
	BoxComponent->SetRelativeScale3D(FVector(2.f, 100.f, 100.f));
	BoxComponent->SetRelativeLocation(FVector(440.f, 0.f, 290.f));

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(FName("Arrow"));
	ArrowComponent->SetupAttachment(CustomRootComponent);
	ArrowComponent->SetRelativeLocation(FVector(1000.f, 0.f, 0.f ));

	//Dont forget the Colision setup for the Box Component
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMT_FloorTerrain::OnBoxBeginOverlap);
	
}

void AMT_FloorTerrain::BeginPlay() {
	Super::BeginPlay();
	SetupObstacles();
}


void AMT_FloorTerrain::SetupObstacles() {
	for (int i = 0; i < 3; i++) {
		FVector ObstaclePosition = FVector(FMath::RandRange(-500, 500),FMath::RandRange(-700, 700) , 0.f);

		AMT_Obstacle* obstacle = GetWorld()->SpawnActor<AMT_Obstacle>(ObstacleClass);
		if (IsValid(obstacle)) {
			obstacle->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			obstacle->SetActorRelativeLocation(ObstaclePosition);
		}else {
			UE_LOG(LogTemp, Warning, TEXT("no es valido :D"))
		}
	}
}

void AMT_FloorTerrain::OnBoxBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult) {
	
	AMechanicsTestCharacter* player = Cast<AMechanicsTestCharacter>(OtherActor);
	AMechanicsTestGameMode* gameMode = Cast<AMechanicsTestGameMode>(GetWorld()->GetAuthGameMode());
	gameMode->ExtendFloor();
}
