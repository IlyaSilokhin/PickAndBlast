// PickAndBlast All Rights Reserved.

#include "Items/PABBombItem.h"
#include "Character/PABBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogBombItem, All, All);

void APABBombItem::DoItemAction()
{
    OverlappedCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
    OverlappedCharacter->TakeDamage(Damage, FDamageEvent {}, nullptr, this);

    FTimerHandle StunCharacterTimerHandle;
    GetWorldTimerManager().SetTimer(StunCharacterTimerHandle, this, &APABBombItem::RepairMovement, BombStunTime, false);

    Super::DoItemAction();
}

void APABBombItem::RepairMovement()
{
    if (OverlappedCharacter->ItemTakenTimes == 1)
    {
        OverlappedCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
        UE_LOG(LogBombItem, Display, TEXT("Movement repaired!"));
    }
    OverlappedCharacter->ItemTakenTimes--;
    Destroy();
}

void APABBombItem::ItemTaken()
{
    MeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    MeshComponent->SetVisibility(false, true);
}