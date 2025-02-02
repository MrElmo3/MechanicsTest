// Copyright Epic Games, Inc. All Rights Reserved.


#include "MechanicsTest/Public/TP_WeaponComponent.h"
#include "MechanicsTest/Public/MechanicsTestCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "CableComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent(){
	// Default offset from the character location for projectiles to spawn

	CableComponent = CreateDefaultSubobject<UCableComponent>(TEXT("Cable"));
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	CableComponent->SetupAttachment(this);

	CableComponent->SetRelativeLocation(FVector(0.f, 60.f, 10.f));
	CableComponent->NumSegments = 1;
	CableComponent->EndLocation = FVector(0, 1000.f, 0.f);
	
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
	HookDistance = 3000.f;
	HookForce = 250000.f;
}


void UTP_WeaponComponent::Fire(){
	if (Character == nullptr || Character->GetController() == nullptr || !Character->GetCanGrap()){
		return;
	}

	// Try and shoot the hook
	if(GetWorld()) {
		FVector offset = Character->GetFirstPersonCameraComponent()->GetForwardVector() * 70.f;
		FVector start = Character->GetFirstPersonCameraComponent()->GetComponentLocation() + offset;
		FVector end = start + (Character->GetFirstPersonCameraComponent()->GetForwardVector() * HookDistance);
		FHitResult hit;
		bool actorHit = GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Pawn);

		if(actorHit && hit.GetActor() != Character) {
			Character->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
			CableComponent->SetVisibility(true);
			GrabPoint = hit.Location;
			Character->SetIsGrapping(true);
		}
	}
	
	// Try and play the sound if specified
	if (FireSound != nullptr){
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
	
	// Try and play a firing animation if specified
	if (FireAnimation != nullptr){
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr){
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}


void UTP_WeaponComponent::ReleaseFire() {
	Character->SetIsGrapping(false);
	Character->GetCharacterMovement()->SetMovementMode(MOVE_Falling);
	CableComponent->SetVisibility(false);
}


void UTP_WeaponComponent::AttachWeapon(AMechanicsTestCharacter* TargetCharacter){
	Character = TargetCharacter;
	if (Character == nullptr){
		return;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
	
	// switch bHasRifle so the animation blueprint can switch to another animation set
	Character->SetHasRifle(true);
	Character->SetCanGrap(true);

	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController())){
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())){
			
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent =
			Cast<UEnhancedInputComponent>(PlayerController->InputComponent)){
			
			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered,
				this, &UTP_WeaponComponent::Fire);
			EnhancedInputComponent->BindAction(ReleaseFireAction, ETriggerEvent::Completed,
				this, &UTP_WeaponComponent::ReleaseFire);
		}
	}
}


void UTP_WeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction) {
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Character == nullptr){
		return;
	}
	if(Character->GetIsGrapping()) {
		CableComponent->EndLocation =
			UKismetMathLibrary::InverseTransformLocation(GetComponentTransform(), GrabPoint);
		FVector forceDirection = GrabPoint - Character->GetActorLocation();
		forceDirection.Normalize();
		Character->GetCharacterMovement()->AddForce(forceDirection * HookForce);
	}

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *GetChildComponent(1)->GetName())
}


void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason){
	if (Character == nullptr){
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController())){
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())){
			
			Subsystem->RemoveMappingContext(FireMappingContext);
		}
	}
}