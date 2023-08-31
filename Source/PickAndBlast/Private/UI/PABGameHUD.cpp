// PickAndBlast All Rights Reserved.


#include "UI/PABGameHUD.h"
#include "Blueprint/UserWidget.h"

void APABGameHUD::BeginPlay() 
{
    Super::BeginPlay();

    if (!GameWidgetClass)
        return;

    UUserWidget* GameWidget = CreateWidget<UUserWidget>(GetWorld(), GameWidgetClass);
    GameWidget->AddToViewport();
}