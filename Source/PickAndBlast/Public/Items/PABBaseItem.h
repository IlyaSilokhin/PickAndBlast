// PickAndBlast All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PABBaseItem.generated.h"

UCLASS()
class PICKANDBLAST_API APABBaseItem : public AActor
{
    GENERATED_BODY()

public:
    APABBaseItem();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
    FVector2D SpawnVectorRate = FVector2D(1.0f, 5.0f);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = "0.0"))
    float Speed = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = "0.0"))
    float MoveTimerRate = 1.0f;

public:
    virtual void Tick(float DeltaTime) override;

    FVector2D GetSpawnVectorRate() const { return SpawnVectorRate; }

private:
    void MoveItems();

    FTimerHandle MoveTimerHandle;
};
