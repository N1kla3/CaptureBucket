// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CBAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class CAPTUREBUCKET_API UCBAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRepHealth)
		FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UCBAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRepBaseHealth)
		FGameplayAttributeData BaseHealth;
	ATTRIBUTE_ACCESSORS(UCBAttributeSet, BaseHealth)
	
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRepMaxHealth)
		FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UCBAttributeSet, MaxHealth)

	
	UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRepMana)
		FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UCBAttributeSet, Mana)

	UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRepBaseMana)
		FGameplayAttributeData BaseMana;
	ATTRIBUTE_ACCESSORS(UCBAttributeSet, BaseMana)
	
	UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRepMaxMana)
		FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UCBAttributeSet, MaxMana)

	
	UPROPERTY(BlueprintReadOnly, Category = "Armor", ReplicatedUsing = OnRepPhysicalArmor)
		FGameplayAttributeData PhyshicalArmor;
	ATTRIBUTE_ACCESSORS(UCBAttributeSet, PhyshicalArmor)

	UPROPERTY(BlueprintReadOnly, Category = "Armor", ReplicatedUsing = OnRepBasePhysicalArmor)
		FGameplayAttributeData BasePhysicalArmor;
	ATTRIBUTE_ACCESSORS(UCBAttributeSet, BasePhysicalArmor)
	
	UPROPERTY(BlueprintReadOnly, Category = "Armor", ReplicatedUsing = OnRepMagicArmor)
		FGameplayAttributeData MagiclArmor;
	ATTRIBUTE_ACCESSORS(UCBAttributeSet, MagiclArmor)

	UPROPERTY(BlueprintReadOnly, Category = "Armor", ReplicatedUsing = OnRepBaseMagicArmor)
		FGameplayAttributeData BaseMagicArmor;
	ATTRIBUTE_ACCESSORS(UCBAttributeSet, BaseMagicArmor)
	
protected:

	UFUNCTION()
	void OnRepHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRepBaseHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRepMaxHealth(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRepMana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRepBaseMana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRepMaxMana(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRepPhysicalArmor(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRepBasePhysicalArmor(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRepMagicArmor(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRepBaseMagicArmor(const FGameplayAttributeData& OldValue);
};
