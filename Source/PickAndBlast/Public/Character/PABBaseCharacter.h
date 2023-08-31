// PickAndBlast All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PABCoreTypes.h"
#include "PABBaseCharacter.generated.h"

class UPABHealthComponent;

UCLASS()
class PICKANDBLAST_API APABBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    APABBaseCharacter();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UPABHealthComponent* HealthComponent;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    uint32 ItemTakenTimes = 0;

    FOnScoreChangedSignature OnScoreChanged;

private:
    void MoveRight(float Amount);

    void OnDeath();
};
