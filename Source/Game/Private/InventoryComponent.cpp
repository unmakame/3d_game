#include "InventoryComponent.h"
#include "Weapon.h"

UInventoryComponent::UInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    MaxMedkits = 3;
    MedkitCount = 0;
    MaxGrenades = 5;
    GrenadeCount = 0;
    ActiveWeaponIndex = 0;
}

void UInventoryComponent::BeginPlay()
{
    Super::BeginPlay();
    InitializeAmmo();
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

AWeapon* UInventoryComponent::GetActiveWeapon() const
{
    if (Weapons.IsValidIndex(ActiveWeaponIndex))
    {
        return Weapons[ActiveWeaponIndex];
    }
    return nullptr;
}

void UInventoryComponent::SwitchWeapon(int32 Index)
{
    if (Weapons.IsValidIndex(Index) && Index != ActiveWeaponIndex)
    {
        ActiveWeaponIndex = Index;
        OnWeaponSwitched();
    }
}

bool UInventoryComponent::AddWeapon(AWeapon* Weapon)
{
    if (Weapon && Weapons.Num() < 5)
    {
        Weapons.Add(Weapon);
        return true;
    }
    return false;
}

void UInventoryComponent::RemoveWeapon(int32 Index)
{
    if (Weapons.IsValidIndex(Index))
    {
        Weapons.RemoveAt(Index);
        if (ActiveWeaponIndex >= Weapons.Num())
        {
            ActiveWeaponIndex = FMath::Max(0, Weapons.Num() - 1);
        }
    }
}

int32 UInventoryComponent::AddMedkits(int32 Amount)
{
    int32 CanAdd = FMath::Min(Amount, MaxMedkits - MedkitCount);
    MedkitCount += CanAdd;
    OnItemsChanged();
    return CanAdd;
}

bool UInventoryComponent::UseMedkit()
{
    if (MedkitCount > 0)
    {
        MedkitCount--;
        OnItemsChanged();
        return true;
    }
    return false;
}

int32 UInventoryComponent::GetMedkitCount() const
{
    return MedkitCount;
}

int32 UInventoryComponent::AddGrenades(int32 Amount)
{
    int32 CanAdd = FMath::Min(Amount, MaxGrenades - GrenadeCount);
    GrenadeCount += CanAdd;
    OnItemsChanged();
    return CanAdd;
}

bool UInventoryComponent::UseGrenade()
{
    if (GrenadeCount > 0)
    {
        GrenadeCount--;
        OnItemsChanged();
        return true;
    }
    return false;
}

void UInventoryComponent::AddAmmo(const FString& WeaponType, int32 Amount)
{
    if (AmmoReserves.Contains(WeaponType))
    {
        AmmoReserves[WeaponType] += Amount;
    }
    else
    {
        AmmoReserves.Add(WeaponType, Amount);
    }
    OnItemsChanged();
}

int32 UInventoryComponent::GetAmmoReserve(const FString& WeaponType) const
{
    if (AmmoReserves.Contains(WeaponType))
    {
        return AmmoReserves[WeaponType];
    }
    return 0;
}

void UInventoryComponent::InitializeWeapons()
{
    // Создание начального оружия в Blueprintе
}

void UInventoryComponent::InitializeAmmo()
{
    AmmoReserves.Add("Pistol", 999); // Бесконечные патроны
    AmmoReserves.Add("M16", 90);
    AmmoReserves.Add("AK", 60);
    AmmoReserves.Add("Grenade", 0);
    AmmoReserves.Add("Rocket", 0);
}
