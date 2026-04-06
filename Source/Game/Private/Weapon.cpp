#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"

AWeapon::AWeapon()
{
    PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

    Damage = 15;
    FireRate = 5.0f;
    ReloadTime = 1.5f;
    MagazineCapacity = 12;
    AmmoCurrent = 12;
    bInfiniteAmmo = false;
    bIsReloading = false;
    ReloadTimer = 0.0f;
    FireTimer = 0.0f;
}

void AWeapon::BeginPlay()
{
    Super::BeginPlay();
}

void AWeapon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateFireTimer(DeltaTime);
    UpdateReloadTimer(DeltaTime);
}

void AWeapon::Fire()
{
    if (!CanFire()) return;

    OnFired();
    ConsummAmmo();
    FireTimer = 1.0f / FireRate;
}

void AWeapon::Reload()
{
    if (!CanReload()) return;

    bIsReloading = true;
    ReloadTimer = ReloadTime;
    OnReloadStarted();
}

void AWeapon::StopFiring()
{
    FireTimer = 0.0f;
}

bool AWeapon::CanFire() const
{
    return !bIsReloading && FireTimer <= 0.0f && (AmmoCurrent > 0 || bInfiniteAmmo);
}

bool AWeapon::CanReload() const
{
    return !bIsReloading && AmmoCurrent < MagazineCapacity && !bInfiniteAmmo;
}

int32 AWeapon::GetCurrentAmmo() const
{
    return AmmoCurrent;
}

int32 AWeapon::GetMagazineCapacity() const
{
    return MagazineCapacity;
}

void AWeapon::UpdateFireTimer(float DeltaTime)
{
    if (FireTimer > 0.0f)
    {
        FireTimer -= DeltaTime;
    }
}

void AWeapon::UpdateReloadTimer(float DeltaTime)
{
    if (bIsReloading)
    {
        ReloadTimer -= DeltaTime;
        if (ReloadTimer <= 0.0f)
        {
            bIsReloading = false;
            AmmoCurrent = MagazineCapacity;
            OnReloadFinished();
        }
    }
}

void AWeapon::ConsummAmmo()
{
    if (!bInfiniteAmmo && AmmoCurrent > 0)
    {
        AmmoCurrent--;
    }
}
