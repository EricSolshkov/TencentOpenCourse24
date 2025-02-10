// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Test54GameMode.generated.h"

class UScoreBoard;
class UInGameHUDControl;

UENUM()
enum class ETest54GamePhase
{
	Loading = 0,
	InGame = 1,
	GameOver = 2,
};

UCLASS(minimalapi)
class ATest54GameMode : public AGameModeBase
{
	GENERATED_BODY()
private:
	UPROPERTY()
	UClass* InGameHUDClass;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APlayerController* PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETest54GamePhase GamePhase;

	UPROPERTY(Category="Gameplay", EditAnywhere, BlueprintReadWrite)
	int32 CubeScore = 5;

	UPROPERTY(Category="Gameplay", EditAnywhere, BlueprintReadWrite)
	float CubeScale = 5.0f;

	UPROPERTY(Category="Gameplay", EditAnywhere, BlueprintReadWrite)
	int32 BonusRate = 2;

	UPROPERTY(Category="Gameplay", EditAnywhere, BlueprintReadWrite)
	int32 BonusCount = 5;

	UPROPERTY(Category="Gameplay", EditAnywhere, BlueprintReadWrite)
	float TimeLimit = 120.0f;

	UPROPERTY()
	UScoreBoard* ScoreBoard;

	UPROPERTY()
	UInGameHUDControl* InGameHUD;

public:
	ATest54GameMode();

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;
};



