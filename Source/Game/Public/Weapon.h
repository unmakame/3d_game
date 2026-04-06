#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

/**
 * Базовый класс для всех видов оружия
 */
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    EWT_Pistol UMETA(DisplayName = "Pistol"),
    EWT_M16Rifle UMETA(DisplayName = "M16 Rifle"),
    EWT_AKRifle UMETA(DisplayName = "AK Rifle"),
    EWT_Grenade UMETA(DisplayName = "Grenade"),
    EWT_RocketLauncher UMETA(DisplayName = "Rocket Launcher"),
    EWT_Max UMETA(DisplayName = "Max")
};

UCLASS()
class FNAF_SHOOTER_API AWeapon : public AActor
{
    GENERATED_BODY()

public:
    AWeapon();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // ===== Основные параметры =====
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
    EWeaponType WeaponType;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
    FString WeaponName;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
    int32 Damage;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
    float FireRate; // выстрелов в секунду

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
    float ReloadTime;

    // ===== Патроны =====
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
    int32 MagazineCapacity;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
    int32 AmmoCurrent;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
    bool bInfiniteAmmo;

    // ===== Состояние =====
    bool bIsReloading;
    float ReloadTimer;
    float FireTimer;

    // ===== Методы стрельбы =====
    virtual void Fire();
    virtual void Reload();
    virtual void StopFiring();
    
    bool CanFire() const;
    bool CanReload() const;
    int32 GetCurrentAmmo() const;
    int32 GetMagazineCapacity() const;

    // ===== События =====
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
    void OnFired();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
    void OnReloadStarted();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
    void OnReloadFinished();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class USkeletalMeshComponent* MeshComponent;

    void UpdateFireTimer(float DeltaTime);
    void UpdateReloadTimer(float DeltaTime);
    void ConsummAmmo();
};
