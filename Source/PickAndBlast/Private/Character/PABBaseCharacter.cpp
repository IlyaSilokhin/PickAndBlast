// PickAndBlast All Rights Reserved.

#include "Character/PABBaseCharacter.h"
#include "Components/PABHealthComponent.h"

APABBaseCharacter::APABBaseCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    HealthComponent = CreateDefaultSubobject<UPABHealthComponent>(TEXT("HealthComponent"));

    HealthComponent->OnDeath.AddUObject(this, &APABBaseCharacter::OnDeath);
}

void APABBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
    check(HealthComponent);

    OnScoreChanged.Broadcast(0);
    HealthComponent->OnHealthChanged.Broadcast(HealthComponent->GetMaxHealth());
}

void APABBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APABBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveRight", this, &APABBaseCharacter::MoveRight);
}

void APABBaseCharacter::MoveRight(float Amount)
{
    if (!Controller || Amount == 0.0f)
        return;
    AddMovementInput(FVector(-1.0f, 0.0f, 0.0f), Amount);
}

void APABBaseCharacter::OnDeath() 
{
    TurnOff();
    DisableInput(Cast<APlayerController>(Controller));
    //TODO: Set match state to "GAME_OVER"
}