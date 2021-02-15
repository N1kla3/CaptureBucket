// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "DefaultPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class CAPTUREBUCKET_API ADefaultPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ADefaultPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY()
	UAbilitySystemComponent* m_AbilityComponent;	
};
