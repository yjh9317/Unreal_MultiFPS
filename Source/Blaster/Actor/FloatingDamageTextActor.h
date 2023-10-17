// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingDamageTextActor.generated.h"

class UWidgetComponent;
class UDamageText;
UCLASS()
class BLASTER_API AFloatingDamageTextActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AFloatingDamageTextActor();
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(Category = "FloatingTextActor")
	void Initialize(const FText& text);

	FORCEINLINE const FVector& GetAnchorLocation() const { return AnchorLocation; }
protected:
	virtual void BeginPlay() override;


private:
	// The Location to which the text is anchored;
	FVector AnchorLocation;

	UPROPERTY()
	FText Text;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess="true"))
	TSubclassOf<UDamageText> DamageTextClass;

	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess="true"))
	UWidgetComponent* WidgetComponent;

	UFUNCTION()
	void HandleAnimFinished();
};
