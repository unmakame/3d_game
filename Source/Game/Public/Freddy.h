#pragma once

#include "CoreMinimal.h"
#include "BaseAnimatornic.h"
#include "Freddy.generated.h"

/**
 * Фредди - медленный, но сильный враг
 * Особенность: игнорирует первый хит за раунд
 */
UCLASS()
class FNAF_SHOOTER_API AFreddy : public ABaseAnimatornic
{
    GENERATED_BODY()

public:
    AFreddy();
    virtual void BeginPlay() override;

    virtual void TakeDamage(float DamageAmount) override;
    virtual void AttackPlayer() override;

private:
    bool bHitIgnoredThisRound;
    float AttackRoundTimer;
};
