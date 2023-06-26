// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Health = 100;

	Temperature = 23;

	Hunger = 100;
	TemperatureDamagePerSecond = 0;
	
}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();
	Day = 1;
	Temperature = -2;
	Health = 100;
	Hunger = 100;
	TemperatureDamagePerSecond = 0;
	HungerDamagePerSecond = 0;
	UE_LOG(LogTemp, Log, TEXT("[BeginPlay] BEGIN"));
	UE_LOG(LogTemp, Log, TEXT("[BeginPlay] VIDA: %d"), Health);
	UE_LOG(LogTemp, Log, TEXT("[BeginPlay] TEMPERATURA: %d"), Temperature);
	UE_LOG(LogTemp, Log, TEXT("[BeginPlay] HAMBRE: %d"), Hunger);
	SecondsInDay = 60; //el dia dura 60 segundos
	DayTimeInSeconds = 0;

	Manana = SecondsInDay / 3;
	Tarde = Manana * 2;
	Noche = Manana * 3;

	UE_LOG(LogTemp, Log, TEXT("[BeginPlay] MANANA: %d"), Manana);
	UE_LOG(LogTemp, Log, TEXT("[BeginPlay] TARDE: %d"), Tarde);
	UE_LOG(LogTemp, Log, TEXT("[BeginPlay] NOCHE: %d"), Noche)
	OnStatsEvent.Broadcast();
	
}


// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	static float Timer = 0.0f;  // Variable para realizar un seguimiento del tiempo transcurrido
	const float Interval = 5.0f; // Intervalo de tiempo en segundos

	Timer += DeltaTime; // Incrementar el temporizador con el tiempo delta

	if (Timer >= Interval)
	{
		CheckDayHour();
		CheckTemperature();
		CheckHunger();

		DecreaseHunger(2);
		Timer -= Interval; // Restablecer el temporizador
	}	

}

void UStatsComponent::CheckDayHour() {
	//Check Day Hour
	DayTimeInSeconds++;
	if (DayTimeInSeconds < Manana) {
		//Es por la mañana, Temperatura = 4 grados
		UE_LOG(LogTemp, Log, TEXT("[CheckDayHour]Es por la manana %d"), DayTimeInSeconds);
		UpdateTemperature(4);
	}
	else if (Manana <= DayTimeInSeconds && DayTimeInSeconds < Tarde) {
		//Es por la tarde, Temperatura = 12 grados
		UE_LOG(LogTemp, Log, TEXT("[CheckDayHour]Es por la tarde %d"), DayTimeInSeconds);
		UpdateTemperature(12);
	}
	else if (Tarde <= DayTimeInSeconds && DayTimeInSeconds <= Noche) {
		UE_LOG(LogTemp, Log, TEXT("[CheckDayHour]Es por la noche %d"), DayTimeInSeconds);
		UpdateTemperature(-2);
	}
	else if (DayTimeInSeconds > Noche) {
		DayTimeInSeconds = 0; //Se hace de dia otra vez
		Day++;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("[TickComponent][FALLO] dayTimeInSeconds se ha vuelto loco."));
	}
}

void UStatsComponent::CheckTemperature() {
	//Check Temperature
	if (Temperature < 0) {
		TemperatureDamagePerSecond = 10;
		DecreaseHealth(TemperatureDamagePerSecond);
		UE_LOG(LogTemp, Log, TEXT("[TickComponent] TEMPERATURA: %d"), Temperature);
		UE_LOG(LogTemp, Log, TEXT("[TickComponent] VIDA: %d"), Health);

	}
	else if (0 <= Temperature && Temperature < 5) {
		TemperatureDamagePerSecond = 5;
		DecreaseHealth(TemperatureDamagePerSecond);
	}
	else if (Temperature >= 5) {
		//Se esta chill
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("[TickComponent][FALLO] Temperatura no contemplada"));
	}
}

void UStatsComponent::CheckHunger() {
	//Check Hunger
	if (30 < Hunger && Hunger <= 50) {
		HungerDamagePerSecond = 2;
		DecreaseHealth(HungerDamagePerSecond);
	}
	else if (10 < Hunger && Hunger <= 30) {
		HungerDamagePerSecond = 5;
		DecreaseHealth(HungerDamagePerSecond);
	}
	else if (Hunger < 10) {
		HungerDamagePerSecond = 10;
		DecreaseHealth(HungerDamagePerSecond);
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("[TickComponent] Hambre > 50"));
	}
}

void UStatsComponent::DecreaseHealth(int bphealth) {
		UE_LOG(LogTemp, Log, TEXT("[UpdateHealth] Restar vida: %d"), bphealth);
		Health -= bphealth;
		OnStatsEvent.Broadcast();	
	}

void UStatsComponent::IncreaseHealth(int bphealth) {
	UE_LOG(LogTemp, Log, TEXT("[UpdateHealth] Sumar vida: %d"), bphealth);
	Health += bphealth;
	OnStatsEvent.Broadcast();
}

void UStatsComponent::DecreaseHunger(int bphunger) {
	UE_LOG(LogTemp, Log, TEXT("[UpdateHunger] Restar hambre: %d"), bphunger);
	Hunger -= bphunger;
	OnStatsEvent.Broadcast();
}

void UStatsComponent::IncreaseHunger(int bphunger) {
	UE_LOG(LogTemp, Log, TEXT("[UpdateHunger] Sumar hambre: %d"), bphunger);
	Hunger += bphunger;
	OnStatsEvent.Broadcast();
}

void UStatsComponent::UpdateTemperature(int temperature) {
	UE_LOG(LogTemp, Log, TEXT("[UpdateTemperature]  %d"), temperature);
	Temperature = temperature;
	OnStatsEvent.Broadcast();
}



