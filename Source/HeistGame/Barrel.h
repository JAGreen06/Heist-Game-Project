// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Barrel.generated.h"

class URadialForceComponent;
class ACharacterController;

UCLASS()
class HEISTGAME_API ABarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABarrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent* BarrelMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	URadialForceComponent* ForceComponent;

public:

	void Explode();
};
