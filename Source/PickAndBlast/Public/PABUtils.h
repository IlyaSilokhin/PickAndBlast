#include "GameFramework/Character.h"

#pragma once

class PABUtils
{
public:
    template <typename T>
    static T* GetPABPlayerComponent(ACharacter* OwnerCharacter)
    {
        if (!OwnerCharacter)
            return nullptr;

        UActorComponent* Component = OwnerCharacter->GetComponentByClass(T::StaticClass());
        T* PlayerComponent = Cast<T>(Component);
        if (!PlayerComponent)
            return nullptr;

        return PlayerComponent;
    }
};
