// PickAndBlast All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PABPlayerState.generated.h"

UCLASS()
class PICKANDBLAST_API APABPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    void SetScore(int32 NewScore);
    int32 GetScore() const { return Score; }

    void LogScore();

private:
    int32 Score = 0;
};
