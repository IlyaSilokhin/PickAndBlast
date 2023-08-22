// PickAndBlast All Rights Reserved.

#include "PickAndBlastGameModeBase.h"
#include "Character/PABBaseCharacter.h"
#include "Character/PABPlayerController.h"
#include "Engine/TargetPoint.h"
#include "Items/PABBaseItem.h"
#include "Kismet/GameplayStatics.h"

APickAndBlastGameModeBase::APickAndBlastGameModeBase()
{
    DefaultPawnClass = APABBaseCharacter::StaticClass();
    PlayerControllerClass = APABPlayerController::StaticClass();
}

void APickAndBlastGameModeBase::StartPlay()
{
    Super::StartPlay();

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), SpawnPoints);

    StartSpawnItem();
}

void APickAndBlastGameModeBase::StartSpawnItem()
{
    GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &APickAndBlastGameModeBase::SpawnItem, SpawnDelay, false);
}

void APickAndBlastGameModeBase::SpawnItem()
{
    if (SpawnPoints.Num() != 0)
    {
        const int32 FoundItemClassIndex = FMath::FRand() < BombSpawnProbability ? 1 : 0;
        const int32 RandSpawnPointIndex = (int32)FMath::RandRange(0.0f, (float)SpawnPoints.Num());
        APABBaseItem* SpawnedItem = GetWorld()->SpawnActor<APABBaseItem>(ItemClasses[FoundItemClassIndex], SpawnPoints[RandSpawnPointIndex]->GetActorLocation(), SpawnPoints[RandSpawnPointIndex]->GetActorRotation());

        float SpawnRate = 1.0f;
        if (Items.Num() != 0)
        {
            SpawnRate = FMath::RandRange(SpawnedItem->GetSpawnVectorRate().X, SpawnedItem->GetSpawnVectorRate().Y);
        }
        Items.AddUnique(SpawnedItem);

        GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &APickAndBlastGameModeBase::SpawnItem, SpawnRate, true);
    }
}