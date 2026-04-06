#include "WaveManager.h"
#include "BaseAnimatornic.h"
#include "Freddy.h"
#include "Bonnie.h"
#include "Chica.h"
#include "Foxy.h"

AWaveManager::AWaveManager()
{
    PrimaryActorTick.bCanEverTick = true;

    CurrentWave = 1;
    EnemiesInWave = 1;
    WaveDuration = 120.0f; // 2 минуты на волну
    EnemySpawnInterval = 20.0f;
    MaxSimultaneousEnemies = 5;
    EnemySpawnDistance = 1500.0f;

    bWaveInProgress = false;
    bIsBossFight = false;
    ActiveEnemyCount = 0;
    SpawnTimer = 0.0f;
    WaveTimer = 0.0f;
}

void AWaveManager::BeginPlay()
{
    Super::BeginPlay();

    AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
    if (GameMode)
    {
        PlayerCharacter = Cast<ACharacter>(GameMode->GetPawn());
    }
}

void AWaveManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bWaveInProgress)
    {
        UpdateWaveLogic(DeltaTime);
    }
}

void AWaveManager::StartWave()
{
    bWaveInProgress = true;
    WaveTimer = 0.0f;
    SpawnTimer = 0.0f;

    // Определяем сложность волны
    EnemiesInWave = FMath::Min(1 + CurrentWave, MaxSimultaneousEnemies);

    if (CurrentWave >= 5 && CurrentWave % 5 == 0)
    {
        bIsBossFight = true;
        EnemiesInWave = 1; // Только босс
    }

    OnWaveStarted();
}

void AWaveManager::EndWave()
{
    bWaveInProgress = false;

    for (ABaseAnimatornic* Enemy : ActiveEnemies)
    {
        if (Enemy)
        {
            Enemy->Destroy();
        }
    }
    ActiveEnemies.Empty();
    ActiveEnemyCount = 0;

    OnWaveEnded();
}

void AWaveManager::NextWave()
{
    CurrentWave++;
    bIsBossFight = false;
    StartWave();
}

void AWaveManager::SpawnEnemy(EAnimatornicType EnemyType)
{
    if (ActiveEnemyCount >= MaxSimultaneousEnemies) return;

    FVector SpawnLocation = GetRandomSpawnLocation();

    ABaseAnimatornic* NewEnemy = nullptr;

    switch (EnemyType)
    {
    case EAnimatornicType::EAT_Freddy:
        NewEnemy = GetWorld()->SpawnActor<AFreddy>(SpawnLocation, FRotator::ZeroRotator);
        break;
    case EAnimatornicType::EAT_Bonnie:
        NewEnemy = GetWorld()->SpawnActor<ABonnie>(SpawnLocation, FRotator::ZeroRotator);
        break;
    case EAnimatornicType::EAT_Chica:
        NewEnemy = GetWorld()->SpawnActor<AChica>(SpawnLocation, FRotator::ZeroRotator);
        break;
    case EAnimatornicType::EAT_Foxy:
        NewEnemy = GetWorld()->SpawnActor<AFoxy>(SpawnLocation, FRotator::ZeroRotator);
        break;
    default:
        break;
    }

    if (NewEnemy)
    {
        NewEnemy->TargetPlayer = PlayerCharacter;
        ActiveEnemies.Add(NewEnemy);
        ActiveEnemyCount++;
        OnEnemySpawned(NewEnemy);

        if (bIsBossFight)
        {
            NewEnemy->Health += 170; // Босс версия (Фредди 250 HP)
            OnBossSpawned(NewEnemy);
        }
    }
}

void AWaveManager::OnEnemyDied(ABaseAnimatornic* Enemy)
{
    if (Enemy)
    {
        ActiveEnemies.Remove(Enemy);
        ActiveEnemyCount--;
    }

    if (ActiveEnemyCount == 0 && bWaveInProgress && WaveTimer > EnemySpawnInterval * EnemiesInWave)
    {
        NextWave();
    }
}

void AWaveManager::UpdateWaveLogic(float DeltaTime)
{
    WaveTimer += DeltaTime;
    SpawnTimer += DeltaTime;

    if (SpawnTimer >= EnemySpawnInterval && ActiveEnemyCount < EnemiesInWave)
    {
        EAnimatornicType EnemyType = GetRandomEnemyType();
        SpawnEnemy(EnemyType);
        SpawnTimer = 0.0f;
    }

    // Проверка по времени волны
    if (WaveTimer > WaveDuration)
    {
        NextWave();
    }
}

EAnimatornicType AWaveManager::GetRandomEnemyType()
{
    int32 RandomType = FMath::RandRange(0, 3);

    switch (RandomType)
    {
    case 0:
        return EAnimatornicType::EAT_Freddy;
    case 1:
        return EAnimatornicType::EAT_Bonnie;
    case 2:
        return EAnimatornicType::EAT_Chica;
    case 3:
        return EAnimatornicType::EAT_Foxy;
    default:
        return EAnimatornicType::EAT_Freddy;
    }
}

FVector AWaveManager::GetRandomSpawnLocation()
{
    if (!PlayerCharacter) return FVector::ZeroVector;

    FVector PlayerLocation = PlayerCharacter->GetActorLocation();
    float RandomAngle = FMath::FRand() * 2.0f * PI;
    float RandomDistance = EnemySpawnDistance + FMath::FRand() * 500.0f;

    FVector SpawnLocation = PlayerLocation + FVector(
        FMath::Cos(RandomAngle) * RandomDistance,
        FMath::Sin(RandomAngle) * RandomDistance,
        0.0f
    );

    return SpawnLocation;
}
