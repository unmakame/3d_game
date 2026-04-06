#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseAnimatornic.h"
#include "WaveManager.generated.h"

/**
 * Менеджер волн врагов
 * Отвечает за спавн врагов, управление сложностью
 */
UCLASS()
class FNAF_SHOOTER_API AWaveManager : public AActor
{
    GENERATED_BODY()

public:
    AWaveManager();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // ===== Параметры волн =====
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Waves")
    int32 CurrentWave;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Waves")
    int32 EnemiesInWave;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Waves")
    float WaveDuration;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Waves")
    float EnemySpawnInterval;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Waves")
    int32 MaxSimultaneousEnemies;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Waves")
    float EnemySpawnDistance;

    // ===== Текущее состояние =====
    UPROPERTY(BlueprintReadWrite, Category = "Waves")
    bool bWaveInProgress;

    UPROPERTY(BlueprintReadWrite, Category = "Waves")
    bool bIsBossFight;

    UPROPERTY(BlueprintReadWrite, Category = "Waves")
    int32 ActiveEnemyCount;

    // ===== Методы =====
    void StartWave();
    void EndWave();
    void NextWave();
    void SpawnEnemy(EAnimatornicType EnemyType);
    void OnEnemyDied(ABaseAnimatornic* Enemy);

    // ===== События =====
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
    void OnWaveStarted();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
    void OnWaveEnded();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
    void OnEnemySpawned(ABaseAnimatornic* Enemy);

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
    void OnBossSpawned(ABaseAnimatornic* Boss);

protected:
    UPROPERTY(BlueprintReadWrite, Category = "Waves")
    TArray<ABaseAnimatornic*> ActiveEnemies;

    float SpawnTimer;
    float WaveTimer;
    ACharacter* PlayerCharacter;

private:
    void UpdateWaveLogic(float DeltaTime);
    EAnimatornicType GetRandomEnemyType();
    FVector GetRandomSpawnLocation();
};
