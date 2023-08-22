// PickAndBlast All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PABFollowActor.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PICKANDBLAST_API APABFollowActor : public AActor
{
    GENERATED_BODY()

  public:
    APABFollowActor();

  protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params")
    ACharacter* ActorToFollow = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params")
    float YOffset = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params")
    float CameraDeadZone = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params")
    float ZOffset = 300.0f;

  public:
    virtual void Tick(float DeltaTime) override;

  private:
    float GetNewXLocation();

    float CameraX = GetActorLocation().X;
};
