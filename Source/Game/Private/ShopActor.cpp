#include "ShopActor.h"
#include "PlayerCharacter.h"

AShopActor::AShopActor()
{
    PrimaryActorTick.bCanEverTick = false;

    InitializePrices();
}

void AShopActor::BeginPlay()
{
    Super::BeginPlay();
}

bool AShopActor::BuyItem(APlayerCharacter* Player, EShopItem Item)
{
    if (!Player) return false;

    int32 Price = GetItemPrice(Item);

    if (Player->ScrapCurrency >= Price)
    {
        Player->AddScrap(-Price);

        switch (Item)
        {
        case EShopItem::ESI_Medkit:
            if (Player->Inventory)
            {
                Player->Inventory->AddMedkits(1);
            }
            break;
        case EShopItem::ESI_Grenade:
            if (Player->Inventory)
            {
                Player->Inventory->AddGrenades(1);
            }
            break;
        case EShopItem::ESI_AmmoM16:
            if (Player->Inventory)
            {
                Player->Inventory->AddAmmo("M16", 30);
            }
            break;
        case EShopItem::ESI_AmmoAK:
            if (Player->Inventory)
            {
                Player->Inventory->AddAmmo("AK", 30);
            }
            break;
        case EShopItem::ESI_HealthUpgrade:
            Player->MaxHealth = FMath::Min(Player->MaxHealth + 20, 200);
            break;
        case EShopItem::ESI_DamageUpgrade:
            // Увеличение урона на 10% (реализуется через оружие)
            break;
        case EShopItem::ESI_FireRateUpgrade:
            // Увеличение скорострельности на 15% (реализуется через оружие)
            break;
        case EShopItem::ESI_Radar:
            // Разблокировка радара
            break;
        default:
            break;
        }

        OnItemPurchased(Item);
        return true;
    }

    OnInsufficientFunds();
    return false;
}

int32 AShopActor::GetItemPrice(EShopItem Item) const
{
    if (ItemPrices.Contains(Item))
    {
        return ItemPrices[Item];
    }
    return 0;
}

FString AShopActor::GetItemName(EShopItem Item) const
{
    switch (Item)
    {
    case EShopItem::ESI_Medkit:
        return "Medkit";
    case EShopItem::ESI_Grenade:
        return "Grenade";
    case EShopItem::ESI_AmmoM16:
        return "M16 Ammo (30)";
    case EShopItem::ESI_AmmoAK:
        return "AK Ammo (30)";
    case EShopItem::ESI_DamageUpgrade:
        return "Damage Upgrade +10%";
    case EShopItem::ESI_FireRateUpgrade:
        return "Fire Rate Upgrade +15%";
    case EShopItem::ESI_HealthUpgrade:
        return "Max Health +20";
    case EShopItem::ESI_Radar:
        return "Radar System";
    default:
        return "Unknown Item";
    }
}

FString AShopActor::GetItemDescription(EShopItem Item) const
{
    switch (Item)
    {
    case EShopItem::ESI_Medkit:
        return "Restores 40 HP";
    case EShopItem::ESI_Grenade:
        return "Explosive grenade";
    case EShopItem::ESI_AmmoM16:
        return "30 rounds for M16";
    case EShopItem::ESI_AmmoAK:
        return "30 rounds for AK";
    case EShopItem::ESI_DamageUpgrade:
        return "Permanent +10% damage";
    case EShopItem::ESI_FireRateUpgrade:
        return "Permanent +15% fire rate";
    case EShopItem::ESI_HealthUpgrade:
        return "Increase max health by 20";
    case EShopItem::ESI_Radar:
        return "Shows nearby enemies";
    default:
        return "No description";
    }
}

void AShopActor::InitializePrices()
{
    ItemPrices.Add(EShopItem::ESI_Medkit, 15);
    ItemPrices.Add(EShopItem::ESI_Grenade, 30);
    ItemPrices.Add(EShopItem::ESI_AmmoM16, 20);
    ItemPrices.Add(EShopItem::ESI_AmmoAK, 25);
    ItemPrices.Add(EShopItem::ESI_DamageUpgrade, 100);
    ItemPrices.Add(EShopItem::ESI_FireRateUpgrade, 120);
    ItemPrices.Add(EShopItem::ESI_HealthUpgrade, 80);
    ItemPrices.Add(EShopItem::ESI_Radar, 150);
}
