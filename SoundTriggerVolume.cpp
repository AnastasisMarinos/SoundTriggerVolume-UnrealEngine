// (C)EVOLV 2023 //
 
 
 #include "Volumes/SoundTriggerVolume.h"
 #include "GameFramework/SpringArmComponent.h"
 #include "GameFramework/Actor.h"


 // INITIALIZE ACTOR //
 ASoundTriggerVolume::ASoundTriggerVolume()
 {
  	// Can Tick?
 	PrimaryActorTick.bCanEverTick = false;
 	
 	// INTERACTION SYSTEM //
 	CollisionBoxScale = FVector(100.f, 100.f, 100.f);
 	AudioSourceLength = 0.f;
 	
 	// SOUND SYSTEM //
 	bPlayedSound = false;
 	bCanBeReplayed = false;
 	
 	// Initialize the default root
 	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(FName("DefaultSceneRoot"));
 	SetRootComponent(DefaultSceneRoot);
 	
 	// Initialize the box that handles collisions
 	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("CollisionMesh"));
 	CollisionMesh->SetupAttachment(DefaultSceneRoot);
 	CollisionMesh->SetBoxExtent(CollisionBoxScale);
 	CollisionMesh->SetRelativeLocation(FVector(0.0f,0.0f, 0.0f));

 	// Initialize spring arm
 	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
 	SpringArm->SetupAttachment(DefaultSceneRoot);
 	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
 	SpringArm->TargetArmLength = AudioSourceLength;
 	
 	// Initialize the audio component
 	AudioComponent = CreateDefaultSubobject<UAudioComponent>(FName("AudioComponent"));
 	AudioComponent->SetupAttachment(SpringArm);
 
 }

// HANDLE PROPERTY CHANGES IN LEVEL DESIGNER //
void ASoundTriggerVolume::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
 	Super::PostEditChangeProperty(PropertyChangedEvent);

 	CollisionMesh->SetBoxExtent(CollisionBoxScale);
 	SpringArm->TargetArmLength = AudioSourceLength;
}

 
 // WHEN THE GAME STARTS //
 void ASoundTriggerVolume::BeginPlay()
 {
 	Super::BeginPlay();
 	//Set up the collision system
 	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this,&ASoundTriggerVolume::OverlapBegin);

 	//Set sound effect for the audio component
 	AudioComponent->SetSound(SoundEffect);
 	AudioComponent->Stop();
 }
 
 // WHEN PLAYER INTERACTS WITH THE ACTOR //
 void ASoundTriggerVolume::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
 	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
 {
 	// Trigger Sound Events
 	if(bCanBeReplayed)
 	{
 		if(!AudioComponent->IsPlaying())
 		{
 			AudioComponent->Play(0.0f);
 		}
 		else
 		{
 			AudioComponent->Stop();
 			AudioComponent->Play(0.0f);
 		}
 	}
 	else if(!bPlayedSound)
 	{
 		if(!AudioComponent->IsPlaying())
 		{
 			AudioComponent->Play(0.0f);
 			bPlayedSound = true;
 		}
 	}
 }
