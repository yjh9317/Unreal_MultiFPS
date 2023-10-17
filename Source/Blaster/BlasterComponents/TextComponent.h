// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TextComponent.generated.h"

class AFloatingDamageTextActor;
class UDamageText;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLASTER_API UTextComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTextComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	// UFUNCTION(Client ,Unreliable)
	// void AddFloatingText(FText text, FVector WorldLocation);

	// UFUNCTION(Server ,Unreliable)
	// void ServerAddFloatingText(FText text, FVector WorldLocation);
	
	// UFUNCTION(Server ,Unreliable)
	// void ServerFloatingText(FText text, FVector WorldLocation);
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(Replicated, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AFloatingDamageTextActor> DamageTextClass;

	// space between each damage number
	float TextVerticalSpacing = 40.0f;

	// pawn offset new text damage
	float TextVerticalOffset = 100.0f;

	UFUNCTION()
	void OnTextDestroyed(AActor* DestroyedActor);

	UPROPERTY(Replicated, EditDefaultsOnly ,meta=(AllowPrivateAccess = "true"))
	TArray<AFloatingDamageTextActor*> ActiveTextActor;
};
