// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceManager.h"

// Sets default values for this component's properties
UResourceManager::UResourceManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetInitialValues();
}

void UResourceManager::AddResources(Resources resourceName, int amount)
{
	int newAmount = GetResource(resourceName) + amount;
	Inventory.Add(resourceName, newAmount);
	OnInventoryChange.Broadcast();
}

void UResourceManager::RemoveResources(Resources resourceName, int amount)
{
	int newAmount = this->GetResource(resourceName) - amount;
	Inventory.Add(resourceName, newAmount >= 0 ? newAmount : 0);
	OnInventoryChange.Broadcast();
}

int UResourceManager::GetResource(Resources resourceName)
{
	return Inventory[resourceName];
}

void UResourceManager::SetInitialValues()
{
	Inventory.Add(Resources::Food, 0);
	Inventory.Add(Resources::Stone, 0);
	Inventory.Add(Resources::Wood, 0);
	Inventory.Add(Resources::Metal, 0);
}