// Fill out your copyright notice in the Description page of Project Settings.


#include "Barrel.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ABarrel::ABarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel Mesh"));
	BarrelMesh->SetupAttachment(RootComponent);

	BarrelMesh->SetSimulatePhysics(true);
	ForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("Force Component"));
	ForceComponent->SetupAttachment(BarrelMesh);
}

// Called when the game starts or when spawned
void ABarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABarrel::Explode()
{
	UE_LOG(LogTemp, Warning, TEXT("BOOM"));

	ForceComponent->FireImpulse();
	Destroy();

}

