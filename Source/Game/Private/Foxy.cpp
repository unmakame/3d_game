#include "Foxy.h"

AFoxy::AFoxy()
{
    AnimatornicName = "Foxy";
    Health = 120;
    MaxHealth = 120;
    Damage = 30;
    MovementSpeed = 600.0f; // Нормальная скорость
    AttackCooldown = 2.5f;
    DetectionRange = 3000.0f;

    bIsCharging = false;
    ChargeTimer = 0.0f;
}

void AFoxy::BeginPlay()
{
    Super::BeginPlay();
}

void AFoxy::TakeDamage(float DamageAmount)
{
    bIsCharging = false; // Фокси останавливает атаку при получении урона
    Super::TakeDamage(DamageAmount);
}

void AFoxy::UpdateAI(float DeltaTime)
{
    if (!TargetPlayer) return;

    float DistanceToPlayer = GetDistanceToPlayer();

    if (bIsCharging)
    {
        // Фокси выполняет прямую атаку в сторону игрока
        FVector DirectionToPlayer = (TargetPlayer->GetActorLocation() - GetActorLocation()).GetSafeNormal();
        GetCharacterMovement()->MaxWalkSpeed = 800.0f; // Увеличенная скорость при атаке
        AddMovementInput(DirectionToPlayer, 1.0f);

        ChargeTimer -= DeltaTime;
        if (ChargeTimer <= 0.0f || DistanceToPlayer < 150.0f)
        {
            bIsCharging = false;
        }
    }
    else
    {
        Super::UpdateAI(DeltaTime);

        // Если Фокси видит игрока, начинает атаку
        if (DistanceToPlayer < DetectionRange && DistanceToPlayer > 300.0f && FMath::Rand() % 100 < 70)
        {
            bIsCharging = true;
            ChargeTimer = 3.0f; // Длительность атаки
        }
    }
}
