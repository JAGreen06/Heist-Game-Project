// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtractionPoint.h"
#include "HeistGameMode.h"
#include "CharacterController.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
AExtractionPoint::AExtractionPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Scene Marker Setup.
	SceneMarker = CreateDefaultSubobject<USceneComponent>(TEXT("Extraction Mark"));
	SetRootComponent(SceneMarker);

	//Mesh Setup.
	ExtractionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Extraction Point"));
	ExtractionMesh->SetupAttachment(SceneMarker);

	
	//Collision Setup.
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Bounds"));
	CollisionBox->SetupAttachment(SceneMarker);
	CollisionBox->SetBoxExtent(FVector(300.0f, 300.0f, 200.0f));
	CollisionBox->SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f));
}

// Called when the game starts or when spawned
void AExtractionPoint::BeginPlay()
{
	Super::BeginPlay();	

	GamemodeRef = Cast<AHeistGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AExtractionPoint::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AExtractionPoint::OnOverlapEnd);
}

// Called every frame
void AExtractionPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AExtractionPoint::GetExtractionTimer(FTimerHandle& TimeLeft)
{
	TimeLeft = ExtractionTimer;
}

void AExtractionPoint::ExtractionSuccess()
{
	APawn* myPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	myPawn->DisableInput(UGameplayStatics::GetPlayerController(this, 0)); 
	ControllerRef->ShowNextLevelScreen();
}

void AExtractionPoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	
	//Need to make sure that it is the player in the extraction zone.
	PlayerRef = Cast<APlayerCharacter>(OtherActor);
	if (!PlayerRef) { return; }
	ControllerRef = Cast<ACharacterController>(PlayerRef->GetController());
	if (!ControllerRef) { return; }

	//Need to make sure the player has the jewel before extracting.
	if (!PlayerRef->GetCarryingJewel()) { return; }

	//Set the extraction point in CharacterController to this ExtractionPoint.
	ControllerRef->ExtractionRef = this;
	//Start Extraction time countdown.
	GetWorld()->GetTimerManager().SetTimer(ExtractionTimer, this, &AExtractionPoint::ExtractionSuccess, ExtractionTime, false);
}

void AExtractionPoint::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//Resets the timer when player leaves the extraction zone.
	GetWorld()->GetTimerManager().ClearTimer(ExtractionTimer);
}
