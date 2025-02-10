// Fill out your copyright notice in the Description page of Project Settings.


#include "Test54/Public/Hitable.h"
#include "Components/MeshComponent.h"


// Sets default values for this component's properties
UHitable::UHitable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Score = 5;
}


// Called when the game starts
void UHitable::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHitable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHitable::OnHit()
{
	GetOwner()->Destroy();
}

