// PickAndBlast All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/PABBaseItem.h"
#include "PABBombItem.generated.h"

UCLASS()
class PICKANDBLAST_API APABBombItem : public APABBaseItem
{
    GENERATED_BODY()

protected:
    virtual void DoItemAction() override;
    virtual void ItemTaken() override;

    UPROPERTY(EditDefaultsOnly, Category = "Item", meta = (ClampMin = "0.0"))
    float Damage = 10.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Item")
    float BombStunTime = 3.0f;

private:
    void RepairMovement();
};