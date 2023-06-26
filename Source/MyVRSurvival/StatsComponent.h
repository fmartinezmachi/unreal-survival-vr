// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "StatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStatsEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYVRSURVIVAL_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void CheckTemperature();
	void CheckHunger();
	void CheckDayHour();

		
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Temperature;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Hunger;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 TemperatureDamagePerSecond;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 HungerDamagePerSecond;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Day;
	UFUNCTION(BlueprintCallable)
	void DecreaseHealth(int bphealth);
	UFUNCTION(BlueprintCallable)
	void IncreaseHealth(int bphealth);
	UFUNCTION(BlueprintCallable)
	void DecreaseHunger(int bphunger);
	UFUNCTION(BlueprintCallable)
	void IncreaseHunger(int bphunger);

	void UpdateTemperature(int temperature);
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<UUserWidget> WidgetBlueprintClass;

	UPROPERTY()
		UUserWidget* WidgetInstance;

	UPROPERTY()
		TArray<UImage*> ImagesArray;*/
	UPROPERTY(BlueprintAssignable)
		FStatsEvent OnStatsEvent;
	int SecondsInDay; //duracion de un dia en la isla en segundos
	int DayTimeInSeconds; //hora actual de la isla en segundos.

	int Manana;
	int Tarde;
	int Noche;

	
};
