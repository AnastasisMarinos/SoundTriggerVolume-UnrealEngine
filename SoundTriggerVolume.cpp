// (C)EVOLV //


#include "Interactables/SoundTriggerActor.h"

#include "Character/PlayerCharacter.h"

// INITIALIZE ACTOR //
ASoundTriggerActor::ASoundTriggerActor()
{
 	// Can Tick?
	PrimaryActorTick.bCanEverTick = false;
	
	// INTERACTION SYSTEM //
	CollisionBoxScale = FVector(100.f, 100.f, 100.f);
	
	// SOUND SYSTEM //
	AC_AwayLocation = FVector(500.f, 0.f, 0.f);
	bPlayedSound = false;
	bCanBeReplayed = false;

	// Play sound in the actor location
	bPlayInPlace = true;
	
	// Play sound away from the actors location
	bPlayAway = false;
	
	// Initialize the default root
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(FName("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);
	
	// Initialize the box that handles collisions
	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("CollisionMesh"));
	CollisionMesh->SetupAttachment(DefaultSceneRoot);
	CollisionMesh->SetBoxExtent(FVector(74.0f, 125.0f, 100.0f));
	CollisionMesh->SetRelativeLocation(FVector(0.0f,0.0f, 0.0f));
	
	// Initialize the in place audio component
	AC_InPlace = CreateDefaultSubobject<UAudioComponent>(FName("AC_InPlace"));
	AC_InPlace->SetupAttachment(DefaultSceneRoot);
	AC_InPlace->SetRelativeLocation(FVector(0.0f,0.0f, 180.0f));
	AC_InPlace->SetSound(SoundEffect);
	AC_InPlace->Stop();
	
	// Initialize the away audio component
	AC_Away = CreateDefaultSubobject<UAudioComponent>(FName("AC_Away"));
	AC_Away->SetupAttachment(DefaultSceneRoot);
	AC_Away->SetRelativeLocation(AC_AwayLocation);
	AC_Away->SetSound(SoundEffect);
	AC_Away->Stop();

}

// WHEN THE GAME STARTS //
void ASoundTriggerActor::BeginPlay()
{
	Super::BeginPlay();
	//Set up the collision system
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this,&ASoundTriggerActor::OverlapBegin);
}

// WHEN PLAYER INTERACTS WITH THE ACTOR //
void ASoundTriggerActor::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Error, TEXT("Overlapped"));
	// Trigger Sound Events
	if(bCanBeReplayed)
	{
		if(bPlayInPlace && !AC_InPlace->IsPlaying())
		{
			AC_InPlace->Play(0.0f);
		}
		else if (bPlayAway && !AC_Away->IsPlaying())
		{
			AC_Away->Play(0.0f);
		}
	}
	else if(!bPlayedSound)
	{
		if(bPlayInPlace && !AC_InPlace->IsPlaying())
		{
			AC_InPlace->Play(0.0f);
			bPlayedSound = true;
		}
		else if (bPlayAway && !AC_Away->IsPlaying())
		{
			AC_Away->Play(0.0f);
			bPlayedSound = true;
		}
	}
}
