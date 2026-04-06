#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class AWeapon;

/**
 * Компонент для управления инвентарём игрока
 * Хранит оружие, патроны, аптечки
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FNAF_SHOOTER_API UInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UInventoryComponent();
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // ===== Оружие =====
    UPROPERTY(BlueprintReadWrite, Category = "Weapons")
    TArray<AWeapon*> Weapons;

    UPROPERTY(BlueprintReadWrite, Category = "Weapons")
    int32 ActiveWeaponIndex;

    AWeapon* GetActiveWeapon() const;
    void SwitchWeapon(int32 Index);
    bool AddWeapon(AWeapon* Weapon);
    void RemoveWeapon(int32 Index);

    // ===== Предметы =====
    UPROPERTY(BlueprintReadWrite, Category = "Items")
    int32 MedkitCount;

    UPROPERTY(BlueprintReadWrite, Category = "Items")
    int32 MaxMedkits;

    int32 AddMedkits(int32 Amount);
    bool UseMedkit();
    int32 GetMedkitCount() const;

    // ===== Гранаты =====
    UPROPERTY(BlueprintReadWrite, Category = "Items")
    int32 GrenadeCount;

    UPROPERTY(BlueprintReadWrite, Category = "Items")
    int32 MaxGrenades;

    int32 AddGrenades(int32 Amount);
    bool UseGrenade();

    // ===== Патроны =====
    UPROPERTY(BlueprintReadWrite, Category = "Ammo")
    TMap<FString, int32> AmmoReserves;

    void AddAmmo(const FString& WeaponType, int32 Amount);
    int32 GetAmmoReserve(const FString& WeaponType) const;

    // ===== События =====
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
    void OnWeaponSwitched();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
    void OnItemsChanged();

private:
    void InitializeWeapons();
    void InitializeAmmo();
};
