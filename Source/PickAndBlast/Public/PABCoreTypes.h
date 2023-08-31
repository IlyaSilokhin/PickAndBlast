#pragma once

#include "PABCoreTypes.generated.h"

// Score

DECLARE_MULTICAST_DELEGATE_OneParam(FOnScoreChangedSignature, int32);

// Health

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);
DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);

// Spawning

class APABBaseItem;

USTRUCT(BlueprintType)
struct FItemSpawn
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
    TSubclassOf<APABBaseItem> ItemClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
    float Probability = 50.0f;
};