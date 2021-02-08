// Fill out your copyright notice in the Description page of Project Settings.


#include "CBAttributeSet.h"

#include "Engine/DemoNetDriver.h"

void UCBAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UCBAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCBAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UCBAttributeSet::OnRepHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCBAttributeSet, Health, OldValue);
}

void UCBAttributeSet::OnRepMaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCBAttributeSet, MaxHealth, OldValue);
}
