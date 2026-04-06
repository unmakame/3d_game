#include "Chica.h"

AChica::AChica()
{
    AnimatornicName = "Chica";
    Health = 50;
    MaxHealth = 50;
    Damage = 10;
    MovementSpeed = 400.0f;
    AttackCooldown = 1.5f;
    DetectionRange = 2200.0f;
}

void AChica::BeginPlay()
{
    Super::BeginPlay();
}

void AChica::Die()
{
    Super::Die();
    ExplodeOnDeath();
}

void AChica::ExplodeOnDeath()
{
    // При смерти Чика взрывается и наносит урон окружающим
    // Радиус взрыва: 300 см, урон: 25 HP
    TArray<FHitResult> HitResults;
    FCollisionShape SphereShape = FCollisionShape::MakeSphere(300.0f);
    FVector ExplosionCenter = GetActorLocation();

    if (GetWorld())
    {
        if (GetWorld()->SweepMultiByChannel(
            HitResults,
            ExplosionCenter,
            ExplosionCenter,
            FQuat::Identity,
            ECC_Pawn,
            SphereShape))
        {
            for (const FHitResult& HitResult : HitResults)
            {
                ACharacter* HitCharacter = Cast<ACharacter>(HitResult.GetActor());
                if (HitCharacter && HitCharacter != this)
                {
                    if (ABaseAnimatornic* Enemy = Cast<ABaseAnimatornic>(HitCharacter))
                    {
                        Enemy->TakeDamage(25.0f);
                    }
                }
            }
        }
    }
}
