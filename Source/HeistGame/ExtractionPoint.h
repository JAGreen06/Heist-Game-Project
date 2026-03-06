// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExtractionPoint.generated.h"

class USceneComponent;
class UBoxComponent;
class AHeistGameMode;
class ACharacterController;
class APlayerCharacter;

UCLASS()
class HEISTGAME_API AExtractionPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExtractionPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void GetExtractionTimer(FTimerHandle& TimeLeft);
private:
	UPROPERTY(EditDefaultsOnly, Category = "Extract")
	UStaticMeshComponent* ExtractionMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Extract")
	UBoxComponent* CollisionBox;

	UPROPERTY(EditDefaultsOnly, Category = "Extract")
	USceneComponent* SceneMarker;

	UPROPERTY()
	AHeistGameMode* GamemodeRef;
	UPROPERTY()
	ACharacterController* ControllerRef;
	UPROPERTY()
	APlayerCharacter* PlayerRef;


	UPROPERTY(EditDefaultsOnly, Category = "Timer")
	float ExtractionTime = 5.0f;
	UPROPERTY()
	FTimerHandle ExtractionTimer;

	void ExtractionSuccess();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
