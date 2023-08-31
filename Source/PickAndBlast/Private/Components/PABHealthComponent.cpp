// PickAndBlast All Rights Reserved.

#include "Components/PABHealthComponent.h"

UPABHealthComponent::UPABHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    AActor* Owner = GetOwner();
    if (!Owner)
        return;

    Owner->OnTakeAnyDamage.AddDynamic(this, &UPABHealthComponent::OnTakeDamage);
}

void UPABHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    SetHealth(MaxHealth);
}

void UPABHealthComponent::OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
    if (!DamagedActor || Damage <= 0.0f)
        return;

    SetHealth(Health - Damage);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
}

void UPABHealthComponent::SetHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}