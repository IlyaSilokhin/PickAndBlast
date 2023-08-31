// PickAndBlast All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PABCoreTypes.h"
#include "PickAndBlastGameModeBase.generated.h"

class APABBaseItem;
class ATargetPoint;

UCLASS()
class PICKANDBLAST_API APickAndBlastGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    APickAndBlastGameModeBase();

public:
    virtual void StartPlay() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
    TArray<FItemSpawn> ItemsToSpawn;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FVector2D SpawnVectorRate = FVector2D(1.0f, 5.0f);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
    float SpawnDelay = 5.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float BombSpawnProbability = 0.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = "0.0"))
    float MinSpawnRate = 0.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = "0.0"))
    float ChangeSpawnTimerRate = 10.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = "0.0"))
    float SubstractRate = 0.1f;

private:
    void StartSpawnItem();
    void SpawnItem();

    int32 ChooseItemClassIndex();
    float SumProbabilities();
    int32 DetermineItemIndex(float RandomValue);

    void ChangeTimerRate();

    TArray<AActor*> SpawnPoints;
    TArray<APABBaseItem*> Items;

    FTimerHandle SpawnTimerHandle;
    FTimerHandle ChangeTimerRateHandle;
};