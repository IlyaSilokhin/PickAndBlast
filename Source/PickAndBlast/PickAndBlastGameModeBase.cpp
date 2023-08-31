// PickAndBlast All Rights Reserved.

#include "PickAndBlastGameModeBase.h"
#include "Character/PABBaseCharacter.h"
#include "Character/PABPlayerController.h"
#include "Character/PABPlayerState.h"
#include "Engine/TargetPoint.h"
#include "Items/PABBaseItem.h"
#include "Kismet/GameplayStatics.h"
#include "UI/PABGameHUD.h"

DEFINE_LOG_CATEGORY_STATIC(LogPABGameMode, All, All);

APickAndBlastGameModeBase::APickAndBlastGameModeBase()
{
    DefaultPawnClass = APABBaseCharacter::StaticClass();
    PlayerControllerClass = APABPlayerController::StaticClass();
    HUDClass = APABGameHUD::StaticClass();
    PlayerStateClass = APABPlayerState::StaticClass();
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
    GetWorldTimerManager().SetTimer(ChangeTimerRateHandle, this, &APickAndBlastGameModeBase::ChangeTimerRate, ChangeSpawnTimerRate, true);
}

void APickAndBlastGameModeBase::SpawnItem()
{
    if (SpawnPoints.Num() != 0)
    {
        int32 FoundItemClassIndex = ChooseItemClassIndex();
        UE_LOG(LogPABGameMode, Display, TEXT("FoundItemClassIndex: %d"), FoundItemClassIndex);
        const int32 RandSpawnPointIndex = (int32)FMath::RandRange(0.0f, (float)SpawnPoints.Num());
        APABBaseItem* SpawnedItem = GetWorld()->SpawnActor<APABBaseItem>(ItemsToSpawn[FoundItemClassIndex].ItemClass,          //
                                                                         SpawnPoints[RandSpawnPointIndex]->GetActorLocation(), //
                                                                         SpawnPoints[RandSpawnPointIndex]->GetActorRotation());

        float SpawnRate = SpawnVectorRate.Y;
        if (Items.Num() != 0)
        {
            SpawnRate = FMath::RandRange(SpawnVectorRate.X, SpawnVectorRate.Y);
            UE_LOG(LogPABGameMode, Display, TEXT("Current spawn rate is: %f"), SpawnRate);
        }
        Items.AddUnique(SpawnedItem);

        GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &APickAndBlastGameModeBase::SpawnItem, SpawnRate, true);
    }
}

void APickAndBlastGameModeBase::ChangeTimerRate()
{
    if (SpawnVectorRate.X > MinSpawnRate)
    {
        SpawnVectorRate.X = FMath::Max(SpawnVectorRate.X - SubstractRate, MinSpawnRate);
    }
    else
    {
        SpawnVectorRate.Y = FMath::Max(SpawnVectorRate.Y - SubstractRate, MinSpawnRate);
    }

    UE_LOG(LogPABGameMode, Display, TEXT("Current spawn vector rate is: %f : %f"), SpawnVectorRate.X, SpawnVectorRate.Y);
}

int32 APickAndBlastGameModeBase::ChooseItemClassIndex()
{
    const float RandSumValue = FMath::RandRange(0.0f, SumProbabilities());
    UE_LOG(LogPABGameMode, Display, TEXT("RandSumValue: %f"), RandSumValue);
    return DetermineItemIndex(RandSumValue);
}

float APickAndBlastGameModeBase::SumProbabilities()
{
    float Sum = 0.0f;
    for (FItemSpawn ItemToSpawn : ItemsToSpawn)
    {
        Sum += ItemToSpawn.Probability;
    }
    UE_LOG(LogPABGameMode, Display, TEXT("Sum: %f"), Sum);
    return Sum;
}

int32 APickAndBlastGameModeBase::DetermineItemIndex(float RandomValue)
{
    float Sum = 0.0f;
    for (int32 Index = 0; Index < ItemsToSpawn.Num(); Index++)
    {
        Sum += ItemsToSpawn[Index].Probability;
        if (Sum >= RandomValue)
        {
            UE_LOG(LogPABGameMode, Display, TEXT("DetermineItemIndex Sum: %f"), Sum);
            UE_LOG(LogPABGameMode, Display, TEXT("Index: %d"), Index);
            return Index;
        }
    }

    return 0;
}