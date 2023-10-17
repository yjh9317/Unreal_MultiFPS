// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DamageText.h"

#include "Animation/WidgetAnimation.h"
#include "Components/TextBlock.h"

void UDamageText::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	Initialize.AddDynamic(this,&UDamageText::InitializeText);
	
	FWidgetAnimationDynamicEvent AnimationDynamicEvent;
	AnimationDynamicEvent.BindUFunction(this,FName("OnAnimFinished"));
	
	BindToAnimationFinished(FloatUp, AnimationDynamicEvent);
	
	if(FloatUp)
	{
		PlayAnimation(FloatUp);
	}
}

void UDamageText::InitializeText(FText Text)
{
	if(DisplayText)
	{
		DisplayText->SetText(Text);
	}
}

void UDamageText::OnAnimFinished()
{
	OnAnimFinishedEvent.Broadcast();
}
