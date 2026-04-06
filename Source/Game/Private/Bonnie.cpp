#include "Bonnie.h"

ABonnie::ABonnie()
{
    AnimatornicName = "Bonnie";
    Health = 60;
    MaxHealth = 60;
    Damage = 15;
    MovementSpeed = 350.0f;
    AttackCooldown = 2.0f;
    DetectionRange = 2300.0f;

    FlankerTimer = 0.0f;
    bTryingToFlank = false;
}

void ABonnie::BeginPlay()
{
    Super::BeginPlay();
}

void ABonnie::UpdateAI(float DeltaTime)
{
    Super::UpdateAI(DeltaTime);

    // Бонни пытается атаковать со стороны
    if (bTryingToFlank)
    {
        FlankerTimer -= DeltaTime;
        if (FlankerTimer <= 0.0f)
        {
            bTryingToFlank = false;
        }
    }
    else if (FMath::Rand() % 100 < 30) // 30% шанс начать фланкирование
    {
        bTryingToFlank = true;
        FlankerTimer = 2.0f;
    }
}

void ABonnie::AttackPlayer()
{
    Super::AttackPlayer();
    // Бонни атакует быстрой очередью
}
