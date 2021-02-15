// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerState.h"

ADefaultPlayerState::ADefaultPlayerState()
{
	m_AbilityComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilityComponent"));
	m_AbilityComponent->SetIsReplicated(true);
}

UAbilitySystemComponent* ADefaultPlayerState::GetAbilitySystemComponent() const
{
	return m_AbilityComponent;
}
