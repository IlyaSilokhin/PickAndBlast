// PickAndBlast All Rights Reserved.

#include "Items/PABBaseItem.h"
#include "Character/PABBaseCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Character/PABPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseItem, All, All);

APABBaseItem::APABBaseItem()
{
    PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    SetRootComponent(MeshComponent);

    MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &APABBaseItem::OnItemBeginOverlap);
}

void APABBaseItem::BeginPlay()
{
    Super::BeginPlay();
    check(MeshComponent);

    GetWorldTimerManager().SetTimer(MoveTimerHandle, this, &APABBaseItem::MoveItems, MoveTimerRate, true, 0.0f);
}

void APABBaseItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APABBaseItem::OnItemBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    OverlappedCharacter = Cast<APABBaseCharacter>(OtherActor);
    const bool IsOverlappedItselfClass = Cast<APABBaseItem>(OtherActor) ? true : false;

    if (IsOverlappedItselfClass)
    {
        return;
    }
    else if (!OverlappedCharacter)
    {
        Destroy();
        return;
    }
    ++(OverlappedCharacter->ItemTakenTimes);
    UE_LOG(LogBaseItem, Display, TEXT("Current item taken times: %d"), OverlappedCharacter->ItemTakenTimes);
    DoItemAction();
}

void APABBaseItem::MoveItems()
{
    const FVector CurrentLocation = GetActorLocation();

    FVector Direction = FVector(0.0f, 0.0f, -1.0f);
    float MoveValue = Direction.Z;
    if (Speed > 0.0f)
    {
        MoveValue = CurrentLocation.Z + Direction.Z * Speed;
    }

    SetActorLocation(FVector(CurrentLocation.X, CurrentLocation.Y, MoveValue));
}

void APABBaseItem::DoItemAction()
{
    APABPlayerState* PABPlayerState = Cast<APABPlayerState>(OverlappedCharacter->Controller->PlayerState);
    if (!PABPlayerState)
        return;

    PABPlayerState->SetScore(PABPlayerState->GetScore() + ScoreModifier);
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ItemTakenEffect, GetActorLocation());
    ItemTaken();
}

void APABBaseItem::ItemTaken()
{
    OverlappedCharacter->ItemTakenTimes--;
    Destroy();
}