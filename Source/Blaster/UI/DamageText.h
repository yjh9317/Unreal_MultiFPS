// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageText.generated.h"

class UTextBlock;



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInitialize, FText, Text);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnimFinished);

UCLASS()
class BLASTER_API UDamageText : public UUserWidget
{
	GENERATED_BODY()

	
public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* DisplayText;

	// 프로퍼티가 BindWidgetAnim이지만, 임시가 아닙니다! 를 해결하기 위해 직렬화를 푸는 Transient를 추가
	UPROPERTY(meta=(BindWidgetAnim),Transient)
	UWidgetAnimation* FloatUp;

	virtual void NativeOnInitialized() override;
	
	UFUNCTION()
	void InitializeText(FText Text);

	FInitialize Initialize;

	UFUNCTION()
	void OnAnimFinished();

	FOnAnimFinished OnAnimFinishedEvent;
};
