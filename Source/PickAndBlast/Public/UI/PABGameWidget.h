// PickAndBlast All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "PABGameWidget.generated.h"

class UTextBlock;
class APABBaseCharacter;
class UProgressBar;
class UPABHealthComponent;

UCLASS()
class PICKANDBLAST_API UPABGameWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeOnInitialized() override;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ScoreTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* HealthTextBlock;

    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthBar;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    float HealthThreshold = 30.0f;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    FLinearColor GoodColor = FLinearColor::Green;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    FLinearColor BadColor = FLinearColor::Red;

private:
    void OnScoreChanged(int32 NewScore);
    void SetScoreText(int32 NewScore);

    void OnHealthChanged(float NewHealth);
    void SetHealthPercent(float NewHealth);
    void SetHealthText(float Health);

    UPABHealthComponent* GetHealthComponent() const;
    APABBaseCharacter* GetOwnerCharacter() const;
};
