// PickAndBlast All Rights Reserved.

#include "Items/PABBaseItem.h"

APABBaseItem::APABBaseItem()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APABBaseItem::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(MoveTimerHandle, this, &APABBaseItem::MoveItems, MoveTimerRate, true, 0.0f);
}

void APABBaseItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APABBaseItem::MoveItems()
{
    const FVector CurrentLocation = GetActorLocation();

    FVector Direction = FVector(0.0f, 0.0f, -1.0f);
    float MoveValue = Direction.Z;
    if (Speed > 0.0f)
    {
        MoveValue = CurrentLocation.Z + Direction.Z * Speed;
    }

    SetActorLocation(FVector(CurrentLocation.X, CurrentLocation.Y, MoveValue));
}