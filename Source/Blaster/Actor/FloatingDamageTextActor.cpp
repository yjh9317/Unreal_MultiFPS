#include "Actor/FloatingDamageTextActor.h"

#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "UI/DamageText.h"

AFloatingDamageTextActor::AFloatingDamageTextActor()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetIsReplicated(true);
	SetRootComponent(WidgetComponent);
}

void AFloatingDamageTextActor::BeginPlay()
{
	Super::BeginPlay();

	AnchorLocation = GetActorLocation();

	UUserWidget* Widget = WidgetComponent->GetUserWidgetObject();
	
	if(Widget)
	{
		UDamageText* DamageText = Cast<UDamageText>(Widget);
		DamageText->OnAnimFinishedEvent.AddDynamic(this,&AFloatingDamageTextActor::HandleAnimFinished);
	}
}

void AFloatingDamageTextActor::HandleAnimFinished()
{
	UUserWidget* Widget = WidgetComponent->GetUserWidgetObject();
	if(Widget)
	{
		UDamageText* DamageText = Cast<UDamageText>(Widget);
		this->Destroy();
	}
}

void AFloatingDamageTextActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFloatingDamageTextActor::Initialize(const FText& _text)
{
	Text = _text;
	UUserWidget* Widget = WidgetComponent->GetUserWidgetObject();

	if(Widget)
	{

		UDamageText* DamageText = Cast<UDamageText>(Widget);
		DamageText->Initialize.Broadcast(Text);
	}
}
