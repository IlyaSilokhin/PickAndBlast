// PickAndBlast All Rights Reserved.

#include "UI/PABGameWidget.h"
#include "Character/PABBaseCharacter.h"
#include "Character/PABPlayerState.h"
#include "Components/PABHealthComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "PABCoreTypes.h"
#include "PABUtils.h"

void UPABGameWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    APABBaseCharacter* OwnerCharacter = GetOwnerCharacter();
    if (!OwnerCharacter)
        return;

    OwnerCharacter->OnScoreChanged.AddUObject(this, &UPABGameWidget::OnScoreChanged);

    UPABHealthComponent* HealthComponent = GetHealthComponent();
    if (!HealthComponent)
        return;

    HealthComponent->OnHealthChanged.AddUObject(this, &UPABGameWidget::OnHealthChanged);
}

void UPABGameWidget::OnHealthChanged(float NewHealth)
{
    SetHealthPercent(NewHealth);
    SetHealthText(NewHealth);
}

void UPABGameWidget::SetHealthPercent(float NewHealth)
{
    if (!HealthBar)
        return;

    UPABHealthComponent* HealthComponent = GetHealthComponent();
    if (!HealthComponent)
        return;

    HealthBar->SetFillColorAndOpacity(NewHealth > HealthThreshold ? GoodColor : BadColor);
    HealthBar->SetPercent(HealthComponent->GetHealthPercent());
}

void UPABGameWidget::SetHealthText(float Health)
{
    if (!HealthTextBlock)
        return;

    HealthTextBlock->SetText(FText::FromString(FString::FromInt(Health)));
}

void UPABGameWidget::OnScoreChanged(int32 NewScore)
{
    SetScoreText(NewScore);
}

void UPABGameWidget::SetScoreText(int32 NewScore)
{
    if (!ScoreTextBlock)
        return;

    FString ScoreText = "Score: " + FString::FromInt(NewScore);
    ScoreTextBlock->SetText(FText::FromString(ScoreText));
}

UPABHealthComponent* UPABGameWidget::GetHealthComponent() const
{
    return PABUtils::GetPABPlayerComponent<UPABHealthComponent>(GetOwnerCharacter());
}

APABBaseCharacter* UPABGameWidget::GetOwnerCharacter() const
{
    return GetOwningPlayerPawn<APABBaseCharacter>();
}