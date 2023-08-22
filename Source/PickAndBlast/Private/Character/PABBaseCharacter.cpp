// PickAndBlast All Rights Reserved.

#include "Character/PABBaseCharacter.h"

APABBaseCharacter::APABBaseCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APABBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
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