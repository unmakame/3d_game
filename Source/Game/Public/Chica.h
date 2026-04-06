#pragma once

#include "CoreMinimal.h"
#include "BaseAnimatornic.h"
#include "Chica.generated.h"

/**
 * Чика - быстрая враг
 * Особенность: при смерти взрывается (небольшой урон)
 */
UCLASS()
class FNAF_SHOOTER_API AChica : public ABaseAnimatornic
{
    GENERATED_BODY()

public:
    AChica();
    virtual void BeginPlay() override;

    virtual void Die() override;

private:
    void ExplodeOnDeath();
};
