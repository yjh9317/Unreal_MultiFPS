// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletHole.generated.h"

UCLASS()
class BLASTER_API ABulletHole : public AActor
{
	GENERATED_BODY()
	
public:	
	ABulletHole();
	FORCEINLINE UDecalComponent* GetDecalComponent() const {return DecalComponent; }
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UDecalComponent* DecalComponent;
public:	
};
