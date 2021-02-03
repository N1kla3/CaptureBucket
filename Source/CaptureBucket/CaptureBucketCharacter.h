// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "CaptureBucketCharacter.generated.h"

UCLASS(Blueprintable)
class ACaptureBucketCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACaptureBucketCharacter();
	
	UFUNCTION(BlueprintPure, Category = "Health")
        float GetHealth() const;

	UFUNCTION(BlueprintPure, Category = "Magic")
    float GetMagic() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
    void UpdateHealth(float HealthChange);

	UFUNCTION(BlueprintCallable, Category = "Magic")
    void UpdateMagic(float MagicChange);

	UFUNCTION(BlueprintPure, Category = "Health")
    FText GetHealthIntText() const;

	UFUNCTION(BlueprintPure, Category = "Magic")
    FText GetMagicIntText() const;

	UFUNCTION()
    void DamageTimer();

	UFUNCTION()
    void SetDamageState();

	UFUNCTION()
    void SetMagicValue();

	UFUNCTION()
    void SetMagicState();

	UFUNCTION()
    void SetMagicChange(float MagicChange);

	UFUNCTION(BlueprintPure, Category = "Health")
    bool PlayFlash();

	virtual void Tick(float DeltaSeconds) override;
	
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return m_TopDownCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return m_CameraBoom; }
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return m_CursorToWorld; }
	
	UPROPERTY(EditAnywhere, Category = "Magic")
	class UMaterialInterface* GunDefaultMaterial;

	UPROPERTY(EditAnywhere, Category = "Magic")
	class UMaterialInterface* GunOverheatMaterial;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float m_FullHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float m_Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float m_HealthPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float m_PreviousHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float m_FullMagic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
	float m_Magic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
	float m_MagicPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
	float m_PreviousMagic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
	float m_MagicValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float m_RedFlash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magic")
	UCurveFloat *m_MagicCurve;
	
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* m_TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* m_CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* m_CursorToWorld;
	
	FTimeline m_MyTimeline;
	float m_CurveFloatValue;
	float m_TimelineValue;
	FTimerHandle m_MemberTimerHandle;

	bool bCanUseMagic;
};


