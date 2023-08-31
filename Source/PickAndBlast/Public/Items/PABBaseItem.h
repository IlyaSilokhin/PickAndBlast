// PickAndBlast All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PABBaseItem.generated.h"

class UStaticMeshComponent;
class UNiagaraSystem;
class APABBaseCharacter;

UCLASS()
class PICKANDBLAST_API APABBaseItem : public AActor
{
    GENERATED_BODY()

public:
    APABBaseItem();

protected:
    virtual void BeginPlay() override;
    virtual void DoItemAction();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
    UStaticMeshComponent* MeshComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = "0.0"))
    float Speed = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = "0.0"))
    float MoveTimerRate = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
    UNiagaraSystem* ItemTakenEffect;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
    int32 ScoreModifier = 1;

    APABBaseCharacter* OverlappedCharacter = nullptr;

public:
    virtual void Tick(float DeltaTime) override;

private:
    virtual void ItemTaken();

    UFUNCTION()
    void OnItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep,const FHitResult& SweepResult);

    void MoveItems();

    FTimerHandle MoveTimerHandle;
};