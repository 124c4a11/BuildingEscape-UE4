// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"

#define OUT


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
  // off to improve performance if you don't need them.
  PrimaryComponentTick.bCanEverTick = true;

  // ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
  Super::BeginPlay();

  Owner = GetOwner();

  if (!PressurePlate)
  {
    UE_LOG(LogTemp, Error, TEXT("Missing physics pressure plate"));
  }
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  if (GetTotalMassOfAcotrsOnPlate() > TriggerMass)
  {
    OnOpen.Broadcast();
  }
  else
  {
    OnClose.Broadcast();
  }
}


float UOpenDoor::GetTotalMassOfAcotrsOnPlate()
{
  float TotalMass = 0.f;

  TArray<AActor*> OverlappingActors;
  if (!PressurePlate) { return TotalMass; }
  PressurePlate->GetOverlappingActors(OUT OverlappingActors);

  for (const auto& Actor : OverlappingActors)
  {
    TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();

    UE_LOG(LogTemp, Warning, TEXT("%s on pleasure plate"), *Actor->GetName());
  }

  return TotalMass;
}

