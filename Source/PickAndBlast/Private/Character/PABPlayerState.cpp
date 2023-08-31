// PickAndBlast All Rights Reserved.


#include "Character/PABPlayerState.h"
#include "Character/PABBaseCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogPABPlayerState, All, All);

void APABPlayerState::SetScore(int32 NewScore) 
{
    Score = FMath::Max(NewScore, 0);
    LogScore();
    const auto OwnerCharacter = Cast<APABBaseCharacter>(GetPawn());
    OwnerCharacter->OnScoreChanged.Broadcast(Score);
}

void APABPlayerState::LogScore()
{
    UE_LOG(LogPABPlayerState, Display, TEXT("The current score value is: %d"), Score);
}