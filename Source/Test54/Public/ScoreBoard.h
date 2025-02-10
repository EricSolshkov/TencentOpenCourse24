// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreBoard.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TEST54_API UScoreBoard : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UScoreBoard();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Score;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
