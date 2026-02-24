// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Rifle.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	Weapon = GetWorld()->SpawnActor<ARifle>(RifleClass);
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("RifleSocket"));
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

AActor* AEnemyCharacter::GetPatrolPoint()
{
	if (PatrolPoints.Num() == 0) { return nullptr; }

	AActor* Point = PatrolPoints[index];
	index = (index + 1) % PatrolPoints.Num();
	return Point;
}

