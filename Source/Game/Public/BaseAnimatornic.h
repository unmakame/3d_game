#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseAnimatornic.generated.h"

/**
 * Базовый класс для всех аниматроников (врагов)
 */
UENUM(BlueprintType)
enum class EAnimatornicType : uint8
{
    EAT_Freddy UMETA(DisplayName = "Freddy"),
    EAT_Bonnie UMETA(DisplayName = "Bonnie"),
    EAT_Chica UMETA(DisplayName = "Chica"),
    EAT_Foxy UMETA(DisplayName = "Foxy"),
    EAT_Boss UMETA(DisplayName = "Boss"),
    EAT_Max UMETA(DisplayName = "Max")
};

UENUM(BlueprintType)
enum class EAnimatornicState : uint8
{
    EAS_Idle UMETA(DisplayName = "Idle"),
    EAS_Pursuing UMETA(DisplayName = "Pursuing"),
    EAS_Attacking UMETA(DisplayName = "Attacking"),
    EAS_Damaged UMETA(DisplayName = "Damaged"),
    EAS_Dead UMETA(DisplayName = "Dead"),
    EAS_Max UMETA(DisplayName = "Max")
};

UCLASS()
class FNAF_SHOOTER_API ABaseAnimatornic : public ACharacter
{
    GENERATED_BODY()

public:
    ABaseAnimatornic();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // ===== Основные параметры =====
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animatornic")
    EAnimatornicType AnimatornicType;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animatornic")
    FString AnimatornicName;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animatornic")
    int32 Health;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animatornic")
    int32 MaxHealth;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animatornic")
    int32 Damage;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animatornic")
    float MovementSpeed;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animatornic")
    float AttackCooldown;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animatornic")
    float DetectionRange;

    // ===== Состояние =====
    UPROPERTY(BlueprintReadWrite, Category = "Animatornic")
    EAnimatornicState CurrentState;

    UPROPERTY(BlueprintReadWrite, Category = "Animatornic")
    ACharacter* TargetPlayer;

    bool bIsDead;
    float AttackCooldownTimer;
    float DeathTimer;

    // ===== Методы =====
    virtual void TakeDamage(float DamageAmount);
    virtual void Die();
    virtual void AttackPlayer();
    virtual void UpdateAI(float DeltaTime);
    
    bool CanAttack() const;
    bool CanSeePlayer() const;
    float GetDistanceToPlayer() const;

    // ===== События =====
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
    void OnDamaged();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
    void OnDeath();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
    void OnAttackPlayer();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
    void OnStateChanged(EAnimatornicState NewState);

protected:
    void SetState(EAnimatornicState NewState);
    void PursuePlayer();
    void SpawnLoot();
    float DamageFlashTimer;
    float DamageFlashDuration;

private:
    void UpdateDamageFlash(float DeltaTime);
};
