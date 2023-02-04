// (C)EVOLV //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "SoundTriggerActor.generated.h"

UCLASS()
class AICON_API ASoundTriggerActor : public AActor
{
	GENERATED_BODY()

	// INTERACTION COMPONENTS //
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* CollisionMesh;

	// AUDIO COMPONENTS //
	UPROPERTY(EditDefaultsOnly)
	UAudioComponent* AC_InPlace;
	UPROPERTY(EditDefaultsOnly)
	UAudioComponent* AC_Away;
	
public:	
	// Initializes the actor
	ASoundTriggerActor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// INTERACTION SYSTEM //

	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "INTERACTION SYSTEM")
	FVector CollisionBoxScale;

	// SOUND SYSTEM //
	
	bool bPlayedSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "SOUND SYSTEM")
	FVector AC_AwayLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "SOUND SYSTEM")
	bool bCanBeReplayed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "SOUND SYSTEM")
	bool bPlayInPlace;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "SOUND SYSTEM")
	bool bPlayAway;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "SOUND SYSTEM")
	USoundBase* SoundEffect;
	
};
