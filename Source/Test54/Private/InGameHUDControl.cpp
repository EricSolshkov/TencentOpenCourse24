// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUDControl.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UInGameHUDControl::UpdateTimeLimit(float NewTime)
{
	if(TimeLimitText)
	{
		TimeLimitText->SetText(FText::FromString(FString::Printf(TEXT("Time left %.1f s"), NewTime)));
	}
}

void UInGameHUDControl::UpdateScore(float Score)
{
	if(ScoreText)
	{
		ScoreText->SetText(FText::FromString(FString::Printf( TEXT("Score: %d"), int(Score))));
	}
}

UInGameHUDControl::UInGameHUDControl(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	TimeLimitText = nullptr;
	ScoreText = nullptr;
}

void UInGameHUDControl::NativeConstruct()
{
	Super::NativeConstruct();

	if(UButton* SettingsButton = CastChecked<UButton>(GetWidgetFromName(FName("SettingsButton"))))
	{
		FScriptDelegate OnSettingClickedDelegate;
		OnSettingClickedDelegate.BindUFunction(this, "OnSettingsButtonClicked");
		SettingsButton->OnClicked.Add(OnSettingClickedDelegate);
	}

	TimeLimitText = CastChecked<UTextBlock>(GetWidgetFromName(FName("TimeLimitText")));
	ScoreText = CastChecked<UTextBlock>(GetWidgetFromName(FName("ScoreText")));
}

void UInGameHUDControl::OnSettingsButtonClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Settings btn clicked"));
}
