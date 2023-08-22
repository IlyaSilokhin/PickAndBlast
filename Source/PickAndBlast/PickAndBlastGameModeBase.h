// PickAndBlast All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ToolTip = "Item Class with 1 index must be 'Bomb'"))
    TArray<TSubclassOf<APABBaseItem>> ItemClasses;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
    float SpawnDelay = 5.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float BombSpawnProbability = 0.5f;

  private:
    void StartSpawnItem();
    void SpawnItem();

    TArray<AActor*> SpawnPoints;
    TArray<APABBaseItem*> Items;

    FTimerHandle SpawnTimerHandle;
};
