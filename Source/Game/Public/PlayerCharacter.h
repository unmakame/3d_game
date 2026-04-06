#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InventoryComponent.h"
#include "PlayerCharacter.generated.h"

/**
 * Основной класс игрока
 * Отвечает за здоровье, инвентарь, получение урона и использование предметов
 */
UCLASS()
class FNAF_SHOOTER_API APlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    APlayerCharacter();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // ===== Здоровье =====
    UPROPERTY(BlueprintReadWrite, Category = "Health")
    int32 Health;
    
    UPROPERTY(BlueprintReadWrite, Category = "Health")
    int32 MaxHealth;

    UPROPERTY(BlueprintReadWrite, Category = "Health")
    float DamageFlashAlpha;

    virtual void TakeDamage(float DamageAmount);
    void Heal(int32 Amount);
    bool IsDead() const;

    // ===== Уровень и опыт =====
    UPROPERTY(BlueprintReadWrite, Category = "Progression")
    int32 PlayerLevel;

    UPROPERTY(BlueprintReadWrite, Category = "Progression")
    int32 CurrentXP;

    UPROPERTY(BlueprintReadWrite, Category = "Progression")
    int32 XPForNextLevel;

    UPROPERTY(BlueprintReadWrite, Category = "Progression")
    int32 ScrapCurrency;

    void AddXP(int32 Amount);
    void AddScrap(int32 Amount);
    void LevelUp();

    // ===== Инвентарь =====
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    UInventoryComponent* Inventory;

    // ===== Использование предметов =====
    void UseMediaKit();
    int32 GetMedkitCount() const;
    bool CanUseMedkit() const;

    // ===== Камеры видеонаблюдения =====
    void ToggleCameraMode();
    bool IsInCameraMode() const;

    // ===== Коллбэки =====
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
    void OnDeath();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
    void OnHealthChanged();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
    void OnXPChanged();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class UCameraComponent* FirstPersonCamera;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float WalkSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float SprintSpeed;

    bool bIsSprintings;
    bool bIsCameraMode;
    float DamageFlashTimer;

private:
    void UpdateDamageFlash(float DeltaTime);
    void HandleInput();
};
