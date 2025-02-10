// Copyright Epic Games, Inc. All Rights Reserved.

#include "Test54GameMode.h"

#include "BonusHitable.h"
#include "ScoreBoard.h"
#include "Test54Character.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Public/InGameHUDControl.h"
#include "EngineUtils.h"
#include "Hitable.h"

ATest54GameMode::ATest54GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	InGameHUDClass = nullptr;
	PlayerController = nullptr;
	ScoreBoard = nullptr;
	GameState = nullptr;
}

void ATest54GameMode::BeginPlay()
{
	Super::BeginPlay();

	GamePhase = ETest54GamePhase::InGame;
	
	InGameHUDClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BP_InGameHUD.BP_InGameHUD_C'"));
	
	if(InGameHUDClass)
	{
		PlayerController = GetWorld()->GetFirstPlayerController();
		if(PlayerController)
		{
			ScoreBoard = Cast<UScoreBoard>(PlayerController->GetPawn()->GetComponentByClass(UScoreBoard::StaticClass()));
			InGameHUD = Cast<UInGameHUDControl>(CreateWidget(PlayerController, InGameHUDClass));
			if(InGameHUD)
			{
				InGameHUD->AddToViewport();
				InGameHUD->UpdateTimeLimit(TimeLimit);
			}
		}
	}

	// 随机使一部分Hitable变成BonusHitable
	for(TActorIterator<AActor> It(GetWorld()); It; ++It)
	{
		if(AActor* Actor = *It)
		{
			auto Hitable = Cast<UHitable>(Actor->GetComponentByClass(UHitable::StaticClass()));
			
			if(Hitable && FMath::RandRange(1, 3) == 1)
			{
				if(const auto BonusHitable = NewObject<UBonusHitable>(Actor))
				{
					BonusHitable->Score = Hitable->Score * BonusRate;
					BonusHitable->EnlargeRatio = CubeScale;
					BonusHitable->RegisterComponent();

					Hitable->UnregisterComponent();
					Hitable->DestroyComponent();
					Hitable = nullptr;
				}
			}
		}
	}
}

inline void LogSummary()
{
	
}

void ATest54GameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(GamePhase == ETest54GamePhase::InGame)
	{
		TimeLimit -= DeltaSeconds;
		if(TimeLimit < 0.01f)
		{
			TimeLimit = +0.0f;
			GamePhase = ETest54GamePhase::GameOver;
			LogSummary();
		}
		if(InGameHUD)
		{
			InGameHUD->UpdateTimeLimit(TimeLimit);
			if(ScoreBoard)
				InGameHUD->UpdateScore(ScoreBoard->Score);
		}
	}
	
}
