// (C)EVOLV 2023 //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "SoundTriggerVolume.generated.h"

UCLASS()
class AICON_API ASoundTriggerVolume : public AActor
{
	GENERATED_BODY()

public:
	// INTERACTION COMPONENTS //
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* DefaultSceneRoot;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBoxComponent* CollisionMesh;

	// AUDIO COMPONENTS //
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAudioComponent* AudioComponent;
	
public:	
	// Initializes the actor
	ASoundTriggerVolume();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	virtual void PostEditChangeProperty (FPropertyChangedEvent & PropertyChangedEvent) override;

	// INTERACTION SYSTEM //

	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "INTERACTION SYSTEM")
	FVector CollisionBoxScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "INTERACTION SYSTEM")
	float AudioSourceLength;

	// SOUND SYSTEM //
	
	bool bPlayedSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "SOUND SYSTEM")
	bool bCanBeReplayed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "SOUND SYSTEM")
	USoundBase* SoundEffect;
	
};
