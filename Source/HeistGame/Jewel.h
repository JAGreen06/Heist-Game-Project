// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Jewel.generated.h"

class USphereComponent;
class APlayerCharacter;

UCLASS()
class HEISTGAME_API AJewel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJewel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* jewelMesh;
	UPROPERTY()
	USphereComponent* collisionSphere;
	UPROPERTY()
	APlayerCharacter* characterRef;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
