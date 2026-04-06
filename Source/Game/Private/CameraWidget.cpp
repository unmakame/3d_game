#include "CameraWidget.h"
#include "PlayerCharacter.h"
#include "BaseAnimatornic.h"

void UCameraWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UCameraWidget::NativeDestruct()
{
    Super::NativeDestruct();
}

void UCameraWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (PlayerReference)
    {
        StunCooldownTimer = FMath::Max(0.0f, StunCooldownTimer - InDeltaTime);
        UpdateCameraFeeds();
    }
}

void UCameraWidget::Initialize(APlayerCharacter* Player)
{
    PlayerReference = Player;
    CameraCount = 6;
    ActiveCameraIndex = 0;
    StunCooldown = 20.0f;
    StunCooldownTimer = 0.0f;
    RepairCooldown = 5.0f;
}

void UCameraWidget::SwitchCamera(int32 CameraIndex)
{
    if (CameraIndex >= 0 && CameraIndex < CameraCount)
    {
        ActiveCameraIndex = CameraIndex;
    }
}

void UCameraWidget::NextCamera()
{
    ActiveCameraIndex = (ActiveCameraIndex + 1) % CameraCount;
}

void UCameraWidget::PreviousCamera()
{
    ActiveCameraIndex = (ActiveCameraIndex - 1 + CameraCount) % CameraCount;
}

bool UCameraWidget::StunEnemy()
{
    if (StunCooldownTimer <= 0.0f)
    {
        // Оглушить врага на активной камере на 2 секунды
        StunCooldownTimer = StunCooldown;
        return true;
    }
    return false;
}

bool UCameraWidget::RepairCamera()
{
    // Починить перегоревшую камеру
    return true;
}

void UCameraWidget::UpdateCameraFeeds()
{
    // Обновить отображение всех камер
}

void UCameraWidget::ShowCameraInfo(ABaseAnimatornic* Enemy)
{
    if (Enemy)
    {
        // Показать информацию о враге на выбранной камере
    }
}
