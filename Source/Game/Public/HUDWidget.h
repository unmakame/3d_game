#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class APlayerCharacter;
class AWeapon;

/**
 * Главный HUD интерфейс игры
 */
UCLASS()
class FNAF_SHOOTER_API UHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    // ===== Инициализация =====
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void Initialize(APlayerCharacter* Player);

    // ===== Обновление данных =====
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateHealth(int32 CurrentHealth, int32 MaxHealth);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateAmmo(int32 Current, int32 Magazine, int32 Reserve);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateMedkits(int32 Count);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateXP(int32 Current, int32 NextLevel);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateWeapon(const FString& WeaponName);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void UpdateScrap(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void ShowDamageIndicator();

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void ShowNotification(const FString& Message, FLinearColor Color);

protected:
    UPROPERTY(BlueprintReadWrite, Category = "HUD")
    APlayerCharacter* PlayerReference;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HUD")
    float NotificationDuration;

private:
    void UpdateHUDElements();
};
