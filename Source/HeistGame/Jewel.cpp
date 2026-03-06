// Fill out your copyright notice in the Description page of Project Settings.


#include "Jewel.h"
#include "Components/SphereComponent.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "ExtractionPoint.h"

// Sets default values
AJewel::AJewel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//Jewel Mesh
	jewelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Jewel Mesh"));
	jewelMesh->SetupAttachment(RootComponent);
	jewelMesh->SetRelativeScale3D(FVector(10.0f, 10.0f, 10.0f));

	//Collision Sphere
	collisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	collisionSphere->SetSphereRadius(10.0f);
	collisionSphere->SetCollisionProfileName("Trigger");
	collisionSphere->SetupAttachment(jewelMesh);

}

// Called when the game starts or when spawned
void AJewel::BeginPlay()
{
	Super::BeginPlay();
	collisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AJewel::OnOverlapBegin);
}

// Called every frame
void AJewel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJewel::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	characterRef = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!characterRef) { return; }
	characterRef->SetCarryingJewel(true);
	Destroy();
}




