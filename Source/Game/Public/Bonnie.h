#pragma once

#include "CoreMinimal.h"
#include "BaseAnimatornic.h"
#include "Bonnie.generated.h"

/**
 * Бонни - враг со средней скоростью
 * Особенность: атакует сбоку, быстрее поворачивает
 */
UCLASS()
class FNAF_SHOOTER_API ABonnie : public ABaseAnimatornic
{
    GENERATED_BODY()

public:
    ABonnie();
    virtual void BeginPlay() override;

    virtual void UpdateAI(float DeltaTime) override;
    virtual void AttackPlayer() override;

private:
    float FlankerTimer;
    bool bTryingToFlank;
};
