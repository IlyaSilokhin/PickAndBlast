// PickAndBlast All Rights Reserved.

#include "Character/PABFollowActor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFollowActor, All, All);

APABFollowActor::APABFollowActor()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = false;
    SpringArmComponent->bEnableCameraLag = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArmComponent);

    if (ActorToFollow)
    {
        CameraX = ActorToFollow->GetActorLocation().X;
        SetActorLocation(FVector(CameraX, YOffset, ZOffset));
    }
}

void APABFollowActor::BeginPlay()
{
    Super::BeginPlay();

    check(CameraComponent);
    check(SpringArmComponent);

    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!PlayerCharacter)
        return;

    ActorToFollow = PlayerCharacter;

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (!PlayerController)
        return;

    PlayerController->SetViewTargetWithBlend(this, 0.0f);
    SpringArmComponent->AttachToComponent(ActorToFollow->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
}

void APABFollowActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!ActorToFollow)
        return;

    CameraX = GetNewXLocation();
    SetActorLocation(FVector(CameraX, YOffset, ZOffset));
}

float APABFollowActor::GetNewXLocation()
{
    if (!ActorToFollow)
        return 0.0f;

    const float ActorXLocationSubstractDeadZone = ActorToFollow->GetActorLocation().X - CameraDeadZone;
    const float CameraXLocation = GetActorLocation().X;
    if (ActorXLocationSubstractDeadZone > CameraXLocation)
        return ActorXLocationSubstractDeadZone;

    const float ActorXLocationAddDeadZone = ActorToFollow->GetActorLocation().X + CameraDeadZone;
    if (ActorXLocationAddDeadZone < CameraXLocation)
    {
        return ActorXLocationAddDeadZone;
    }
    else
    {
        return CameraX;
    }
}