#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InventoryComponent.h"
#include "InputActionValue.h"

APlayerCharacter::APlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Не ротируем тело с камерой
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Настройка движения
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->MaxWalkSpeed = 600.0f;
    WalkSpeed = 600.0f;
    SprintSpeed = 1000.0f;

    // Видовая дистанция
    GetCharacterMovement()->MaxWalkSpeedCrouched = 300.0f;

    // Создание камеры
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 0.0f;
    CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 60.0f);
    CameraBoom->bUsePawnControlRotation = true;

    FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FirstPersonCamera->bUsePawnControlRotation = false;

    // Инвентарь
    Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
    Inventory->RegisterComponent();

    // Инициализация параметров
    Health = 100;
    MaxHealth = 100;
    PlayerLevel = 1;
    CurrentXP = 0;
    XPForNextLevel = 100;
    ScrapCurrency = 0;
    bIsSprintings = false;
    bIsCameraMode = false;
    DamageFlashAlpha = 0.0f;
    DamageFlashTimer = 0.0f;
}

void APlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateDamageFlash(DeltaTime);
    HandleInput();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Навигация
    PlayerInputComponent->BindAxis("MoveForward", this, &ACharacter::AddMovementInput, GetActorForwardVector(), 1.0f);
    PlayerInputComponent->BindAxis("MoveRight", this, &ACharacter::AddMovementInput, GetActorRightVector(), 1.0f);

    // Камера
    PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);

    // Действия
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::HandleInput);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APlayerCharacter::HandleInput);
    PlayerInputComponent->BindAction("UseMediaKit", IE_Pressed, this, &APlayerCharacter::UseMediaKit);
    PlayerInputComponent->BindAction("CameraMode", IE_Pressed, this, &APlayerCharacter::ToggleCameraMode);
}

void APlayerCharacter::TakeDamage(float DamageAmount)
{
    Health -= (int32)DamageAmount;
    DamageFlashAlpha = 1.0f;
    DamageFlashTimer = 0.2f;

    if (Health <= 0)
    {
        Health = 0;
        OnDeath();
    }

    OnHealthChanged();
}

void APlayerCharacter::Heal(int32 Amount)
{
    Health = FMath::Min(Health + Amount, MaxHealth);
    OnHealthChanged();
}

bool APlayerCharacter::IsDead() const
{
    return Health <= 0;
}

void APlayerCharacter::AddXP(int32 Amount)
{
    CurrentXP += Amount;
    OnXPChanged();

    if (CurrentXP >= XPForNextLevel)
    {
        LevelUp();
    }
}

void APlayerCharacter::AddScrap(int32 Amount)
{
    ScrapCurrency += Amount;
}

void APlayerCharacter::LevelUp()
{
    PlayerLevel++;
    CurrentXP = 0;
    MaxHealth += 5;
    MaxHealth = FMath::Min(MaxHealth, 200);
    Health = MaxHealth;
    XPForNextLevel = (int32)(100 * FMath::Pow(1.1f, (float)PlayerLevel));

    OnXPChanged();
}

void APlayerCharacter::UseMediaKit()
{
    if (Inventory && Inventory->UseMedkit())
    {
        Heal(40);
    }
}

int32 APlayerCharacter::GetMedkitCount() const
{
    if (Inventory)
    {
        return Inventory->GetMedkitCount();
    }
    return 0;
}

bool APlayerCharacter::CanUseMedkit() const
{
    return Health < MaxHealth && GetMedkitCount() > 0;
}

void APlayerCharacter::ToggleCameraMode()
{
    bIsCameraMode = !bIsCameraMode;
}

bool APlayerCharacter::IsInCameraMode() const
{
    return bIsCameraMode;
}

void APlayerCharacter::UpdateDamageFlash(float DeltaTime)
{
    if (DamageFlashTimer > 0.0f)
    {
        DamageFlashTimer -= DeltaTime;
        DamageFlashAlpha = FMath::Max(0.0f, DamageFlashAlpha - DeltaTime * 5.0f);
    }
}

void APlayerCharacter::HandleInput()
{
    // Логика обработки ввода реализуется через BindAction выше
}
