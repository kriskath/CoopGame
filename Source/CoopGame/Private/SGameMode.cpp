// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameMode.h"


ASGameMode::ASGameMode()
{
	TimeBetweenWaves = 2.0f;
}

void ASGameMode::StartWave()
{
	WaveCount++;

	NumBotsToSpawn = 2 * WaveCount;

	GetWorldTimerManager().SetTimer(TimerHandle_BotSpawner, this, &ASGameMode::SpawnBotTimerElapsed, 1.0f, true, 0.0f);
}

void ASGameMode::SpawnBotTimerElapsed()
{

	SpawnNewBot();

	NumBotsToSpawn--;

	if (NumBotsToSpawn <= 0)
	{
		EndWave();
	}
}


void ASGameMode::EndWave()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_BotSpawner);

	PrepareForNextWave();
}

void ASGameMode::PrepareForNextWave()
{
	FTimerHandle TimerHandle_NextWaveStart;
	GetWorldTimerManager().SetTimer(TimerHandle_NextWaveStart, this, &ASGameMode::StartWave, TimeBetweenWaves, false);

}


void ASGameMode::StartPlay()
{
	Super::StartPlay();

	PrepareForNextWave();
}