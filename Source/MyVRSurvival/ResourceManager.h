// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Resources.h"
#include "ResourceManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryChange);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYVRSURVIVAL_API UResourceManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UResourceManager();

private:
	TMap<Resources, int> Inventory;
	void SetInitialValues();

public:
	UFUNCTION(BlueprintCallable)
		void AddResources(Resources resourceName, int amount);
	UFUNCTION(BlueprintCallable)
		void RemoveResources(Resources resourceName, int amount);
	UFUNCTION(BlueprintCallable)
		int GetResource(Resources resourceName);

	UPROPERTY(BlueprintAssignable)
		FInventoryChange OnInventoryChange;
};
