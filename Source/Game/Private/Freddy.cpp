#include "Freddy.h"

AFreddy::AFreddy()
{
    AnimatornicName = "Freddy";
    Health = 80;
    MaxHealth = 80;
    Damage = 20;
    MovementSpeed = 250.0f;
    AttackCooldown = 3.0f;
    DetectionRange = 2500.0f;

    bHitIgnoredThisRound = false;
    AttackRoundTimer = 0.0f;
}

void AFreddy::BeginPlay()
{
    Super::BeginPlay();
}

void AFreddy::TakeDamage(float DamageAmount)
{
    // Фредди игнорирует первый хит за раунд
    if (bHitIgnoredThisRound)
    {
        Super::TakeDamage(DamageAmount);
    }
    else
    {
        bHitIgnoredThisRound = true;
        AttackRoundTimer = 5.0f; // Раунд длится 5 секунд
    }
}

void AFreddy::AttackPlayer()
{
    if (TargetPlayer && CanAttack())
    {
        Super::AttackPlayer();
        // Фредди наносит больший урон
        if (TargetPlayer->IsA<ACharacter>())
        {
            ACharacter* PlayerChar = Cast<ACharacter>(TargetPlayer);
            // Нанесение урона (будет реализовано через события)
        }
    }
}
