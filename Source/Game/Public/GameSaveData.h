#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameSaveData.generated.h"

/**
 * Структура данных для сохранения
 */
USTRUCT(BlueprintType)
struct FPlayerSaveData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Player")
    int32 Level;

    UPROPERTY(BlueprintReadWrite, Category = "Player")
    int32 MaxHealth;

    UPROPERTY(BlueprintReadWrite, Category = "Player")
    int32 ScrapCurrency;

    UPROPERTY(BlueprintReadWrite, Category = "Player")
    int32 KillCount;

    UPROPERTY(BlueprintReadWrite, Category = "Player")
    int32 HighScore;
};

USTRUCT(BlueprintType)
struct FUpgradeSaveData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Upgrades")
    int32 DamageBonus;

    UPROPERTY(BlueprintReadWrite, Category = "Upgrades")
    int32 FireRateBonus;

    UPROPERTY(BlueprintReadWrite, Category = "Upgrades")
    bool bHasRadar;

    UPROPERTY(BlueprintReadWrite, Category = "Upgrades")
    bool bAutoReload;
};

UCLASS()
class FNAF_SHOOTER_API UGameSaveData : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, Category = "Save")
    FPlayerSaveData PlayerData;

    UPROPERTY(BlueprintReadWrite, Category = "Save")
    FUpgradeSaveData UpgradeData;

    UPROPERTY(BlueprintReadWrite, Category = "Save")
    int32 SaveSlot;

    UPROPERTY(BlueprintReadWrite, Category = "Save")
    FString SaveDateTime;
};
