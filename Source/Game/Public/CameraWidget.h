#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseAnimatornic.h"
#include "CameraWidget.generated.h"

class APlayerCharacter;

/**
 * Интерфейс камер видеонаблюдения (FNaF-стиль)
 */
UCLASS()
class FNAF_SHOOTER_API UCameraWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    // ===== Управление камерами =====
    UFUNCTION(BlueprintCallable, Category = "Camera")
    void Initialize(APlayerCharacter* Player);

    UFUNCTION(BlueprintCallable, Category = "Camera")
    void SwitchCamera(int32 CameraIndex);

    UFUNCTION(BlueprintCallable, Category = "Camera")
    void NextCamera();

    UFUNCTION(BlueprintCallable, Category = "Camera")
    void PreviousCamera();

    // ===== Спецвозможности =====
    UFUNCTION(BlueprintCallable, Category = "Camera")
    bool StunEnemy();

    UFUNCTION(BlueprintCallable, Category = "Camera")
    bool RepairCamera();

    // ===== Обновление отображения =====
    UFUNCTION(BlueprintCallable, Category = "Camera")
    void UpdateCameraFeeds();

    UFUNCTION(BlueprintCallable, Category = "Camera")
    void ShowCameraInfo(ABaseAnimatornic* Enemy);

protected:
    UPROPERTY(BlueprintReadWrite, Category = "Camera")
    APlayerCharacter* PlayerReference;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
    int32 CameraCount;

    UPROPERTY(BlueprintReadWrite, Category = "Camera")
    int32 ActiveCameraIndex;

    UPROPERTY(BlueprintReadWrite, Category = "Camera")
    float StunCooldown;

    UPROPERTY(BlueprintReadWrite, Category = "Camera")
    float RepairCooldown;

private:
    float StunCooldownTimer;
};
