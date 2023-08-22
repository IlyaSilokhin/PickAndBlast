// PickAndBlast All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PABBaseCharacter.generated.h"

UCLASS()
class PICKANDBLAST_API APABBaseCharacter : public ACharacter
{
    GENERATED_BODY()

  public:
    APABBaseCharacter();

  protected:
    virtual void BeginPlay() override;

  public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

  private:
    void MoveRight(float Amount);
};
