// PickAndBlast All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PABGameHUD.generated.h"

class UUserWidget;

UCLASS()
class PICKANDBLAST_API APABGameHUD : public AHUD
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> GameWidgetClass;
};
