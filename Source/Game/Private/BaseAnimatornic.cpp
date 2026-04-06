#include "BaseAnimatornic.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"

ABaseAnimatornic::ABaseAnimatornic()
{
    PrimaryActorTick.bCanEverTick = true;

    AnimatornicName = "Base Animatornic";
    Health = 50;
    MaxHealth = 50;
    Damage = 10;
    MovementSpeed = 300.0f;
    AttackCooldown = 2.0f;
    DetectionRange = 2000.0f;

    bIsDead = false;
    CurrentState = EAnimatornicState::EAS_Idle;
    AttackCooldownTimer = 0.0f;
    DeathTimer = 0.0f;
    DamageFlashTimer = 0.0f;
    DamageFlashDuration = 0.2f;
}

void ABaseAnimatornic::BeginPlay()
{
    Super::BeginPlay();
}

void ABaseAnimatornic::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bIsDead)
    {
        UpdateAI(DeltaTime);
        UpdateDamageFlash(DeltaTime);

        if (AttackCooldownTimer > 0.0f)
        {
            AttackCooldownTimer -= DeltaTime;
        }
    }
    else
    {
        DeathTimer += DeltaTime;
        if (DeathTimer > 5.0f)
        {
            Destroy();
        }
    }
}

void ABaseAnimatornic::TakeDamage(float DamageAmount)
{
    Health -= (int32)DamageAmount;
    DamageFlashTimer = DamageFlashDuration;

    OnDamaged();

    if (Health <= 0)
    {
        Die();
    }
}

void ABaseAnimatornic::Die()
{
    bIsDead = true;
    CurrentState = EAnimatornicState::EAS_Dead;
    GetCharacterMovement()->MaxWalkSpeed = 0.0f;
    OnDeath();
    SpawnLoot();
}

void ABaseAnimatornic::AttackPlayer()
{
    if (TargetPlayer && CanAttack())
    {
        OnAttackPlayer();
        AttackCooldownTimer = AttackCooldown;
    }
}

void ABaseAnimatornic::UpdateAI(float DeltaTime)
{
    if (!TargetPlayer) return;

    float DistanceToPlayer = GetDistanceToPlayer();

    if (DistanceToPlayer < 100.0f)
    {
        SetState(EAnimatornicState::EAS_Attacking);
        AttackPlayer();
    }
    else if (DistanceToPlayer < DetectionRange)
    {
        SetState(EAnimatornicState::EAS_Pursuing);
        PursuePlayer();
    }
    else
    {
        SetState(EAnimatornicState::EAS_Idle);
    }
}

bool ABaseAnimatornic::CanAttack() const
{
    return AttackCooldownTimer <= 0.0f && !bIsDead;
}

bool ABaseAnimatornic::CanSeePlayer() const
{
    if (!TargetPlayer) return false;

    float DistanceToPlayer = GetDistanceToPlayer();
    return DistanceToPlayer <= DetectionRange;
}

float ABaseAnimatornic::GetDistanceToPlayer() const
{
    if (!TargetPlayer) return 99999.0f;
    return FVector::Dist(GetActorLocation(), TargetPlayer->GetActorLocation());
}

void ABaseAnimatornic::SetState(EAnimatornicState NewState)
{
    if (CurrentState != NewState)
    {
        CurrentState = NewState;
        OnStateChanged(NewState);
    }
}

void ABaseAnimatornic::PursuePlayer()
{
    if (!TargetPlayer) return;

    FVector DirectionToPlayer = (TargetPlayer->GetActorLocation() - GetActorLocation()).GetSafeNormal();
    GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
    AddMovementInput(DirectionToPlayer, 1.0f);
}

void ABaseAnimatornic::SpawnLoot()
{
    // Логика спавна лута реализуется в Blueprintе или LootDropper компоненте
}

void ABaseAnimatornic::UpdateDamageFlash(float DeltaTime)
{
    if (DamageFlashTimer > 0.0f)
    {
        DamageFlashTimer -= DeltaTime;
    }
}
