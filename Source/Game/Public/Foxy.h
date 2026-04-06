#pragma once

#include "CoreMinimal.h"
#include "BaseAnimatornic.h"
#include "Foxy.generated.h"

/**
 * Фокси - очень быстрый враг
 * Особенность: бежит прямо на игрока в спринте, пока не получит урон
 */
UCLASS()
class FNAF_SHOOTER_API AFoxy : public ABaseAnimatornic
{
    GENERATED_BODY()

public:
    AFoxy();
    virtual void BeginPlay() override;

    virtual void TakeDamage(float DamageAmount) override;
    virtual void UpdateAI(float DeltaTime) override;

private:
    bool bIsCharging;
    float ChargeTimer;
};
