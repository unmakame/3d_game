#include "HUDWidget.h"
#include "PlayerCharacter.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"

void UHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UHUDWidget::NativeDestruct()
{
    Super::NativeDestruct();
}

void UHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (PlayerReference)
    {
        UpdateHUDElements();
    }
}

void UHUDWidget::Initialize(APlayerCharacter* Player)
{
    PlayerReference = Player;
    UpdateHUDElements();
}

void UHUDWidget::UpdateHealth(int32 CurrentHealth, int32 MaxHealth)
{
    // Обновление полоски здоровья
    // Реализуется через Blueprint компоненты
}

void UHUDWidget::UpdateAmmo(int32 Current, int32 Magazine, int32 Reserve)
{
    // Обновление отображения патронов
}

void UHUDWidget::UpdateMedkits(int32 Count)
{
    // Обновление счётчика аптечек
}

void UHUDWidget::UpdateXP(int32 Current, int32 NextLevel)
{
    // Обновление полоски опыта
}

void UHUDWidget::UpdateWeapon(const FString& WeaponName)
{
    // Обновление иконки оружия
}

void UHUDWidget::UpdateScrap(int32 Amount)
{
    // Обновление счётчика валюты
}

void UHUDWidget::ShowDamageIndicator()
{
    // Показать красную вспышку при получении урона
}

void UHUDWidget::ShowNotification(const FString& Message, FLinearColor Color)
{
    // Показать уведомление
}

void UHUDWidget::UpdateHUDElements()
{
    if (!PlayerReference) return;

    UpdateHealth(PlayerReference->Health, PlayerReference->MaxHealth);
    UpdateMedkits(PlayerReference->GetMedkitCount());
    UpdateXP(PlayerReference->CurrentXP, PlayerReference->XPForNextLevel);
    UpdateScrap(PlayerReference->ScrapCurrency);

    if (PlayerReference->Inventory && PlayerReference->Inventory->GetActiveWeapon())
    {
        AWeapon* Weapon = PlayerReference->Inventory->GetActiveWeapon();
        UpdateWeapon(Weapon->WeaponName);
        UpdateAmmo(Weapon->AmmoCurrent, Weapon->MagazineCapacity, 
                   PlayerReference->Inventory->GetAmmoReserve(Weapon->WeaponName));
    }
}
