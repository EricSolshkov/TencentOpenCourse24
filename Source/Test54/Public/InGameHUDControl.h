// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameHUDControl.generated.h"

class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS()
class TEST54_API UInGameHUDControl : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UTextBlock* TimeLimitText;

	UPROPERTY()
	UTextBlock* ScoreText;

public:
	UFUNCTION()
	void UpdateTimeLimit(float NewTime);

	UFUNCTION()
	void UpdateScore(float Score);
	
protected:
	UInGameHUDControl(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeConstruct() override; 

	UFUNCTION()
	void OnSettingsButtonClicked();
};
