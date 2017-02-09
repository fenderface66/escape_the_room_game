// Robbie Heygate 2016

#include "escape_the_room.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}

void UOpenDoor::OpenDoor()
{

	UE_LOG(LogTemp, Warning, TEXT("OPENED"));
	// Set the door rotation
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{

	// Set the door rotation
	Owner->SetActorRotation(FRotator(0.0f, 0.f, 0.0f));
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll the Trigger Volume
	// If the ActorThatOpens is in the volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		UE_LOG(LogTemp, Warning, TEXT("OPENED"));
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	//Check if its time to close the door
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		UE_LOG(LogTemp, Warning, TEXT("CLOSED"));
		UE_LOG(LogTemp, Warning, TEXT("LAST FOOR OPEN TIME %s"), LastDoorOpenTime);
		UE_LOG(LogTemp, Warning, TEXT("DOOR CLOSE DELAY %s"), DoorCloseDelay);
		CloseDoor();
	}
	
}





