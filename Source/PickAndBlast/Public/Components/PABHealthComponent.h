// PickAndBlast All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "PABCoreTypes.h"
#include "PABHealthComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PICKANDBLAST_API UPABHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPABHealthComponent();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0"))
    float MaxHealth = 100.0f;

public:
    void SetHealth(float NewHealth);
    float GetHealthPercent() const { return Health / MaxHealth; }

    float GetMaxHealth() const { return MaxHealth; }

    FOnHealthChangedSignature OnHealthChanged;
    FOnDeathSignature OnDeath;

private:
    bool IsDead() const { return FMath::IsNearlyZero(Health); }

    float Health = 0.0f;
};
