#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShopActor.generated.h"

class APlayerCharacter;

/**
 * Магазин - продаёт улучшения за валюту Scrap
 */
UENUM(BlueprintType)
enum class EShopItem : uint8
{
    ESI_Medkit UMETA(DisplayName = "Medkit"),
    ESI_Grenade UMETA(DisplayName = "Grenade"),
    ESI_AmmoM16 UMETA(DisplayName = "Ammo M16"),
    ESI_AmmoAK UMETA(DisplayName = "Ammo AK"),
    ESI_DamageUpgrade UMETA(DisplayName = "Damage +10%"),
    ESI_FireRateUpgrade UMETA(DisplayName = "Fire Rate +15%"),
    ESI_HealthUpgrade UMETA(DisplayName = "Max Health +20"),
    ESI_Radar UMETA(DisplayName = "Radar"),
    ESI_Max UMETA(DisplayName = "Max")
};

UCLASS()
class FNAF_SHOOTER_API AShopActor : public AActor
{
    GENERATED_BODY()

public:
    AShopActor();
    virtual void BeginPlay() override;

    // ===== Цены предметов =====
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shop")
    TMap<EShopItem, int32> ItemPrices;

    // ===== Методы покупки =====
    bool BuyItem(APlayerCharacter* Player, EShopItem Item);
    int32 GetItemPrice(EShopItem Item) const;
    FString GetItemName(EShopItem Item) const;
    FString GetItemDescription(EShopItem Item) const;

    // ===== События =====
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
    void OnItemPurchased(EShopItem Item);

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
    void OnInsufficientFunds();

private:
    void InitializePrices();
};
