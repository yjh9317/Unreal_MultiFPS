#include "BlasterComponents/TextComponent.h"

#include "Actor/FloatingDamageTextActor.h"
// #include "Blueprint/WidgetLayoutLibrary.h"
// #include "Engine/UserInterfaceSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

UTextComponent::UTextComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTextComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UTextComponent,DamageTextClass);
	DOREPLIFETIME(UTextComponent,ActiveTextActor);
}

void UTextComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTextComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if(!GetOwner<APawn>()->IsLocallyControlled()) return;

	// const FVector2D viewportSize = UWidgetLayoutLibrary::GetViewportSize(this);
	//
	// if(viewportSize.X < 0.0f || viewportSize.Y <= 0.0f) return;
	//
	// const int32 viewportX = FGenericPlatformMath::FloorToInt(viewportSize.X);
	// const int32 viewportY = FGenericPlatformMath::FloorToInt(viewportSize.Y);
	// const float viewportScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(viewportX,viewportY));
	//
	// if(viewportScale <= 0.0f) return;
	//
	// const FVector CameraLocation = GetOwner<APawn>()->GetController<APlayerController>()->PlayerCameraManager->GetCameraLocation();
	//
	// for(int32 i = 0; i < ActiveTextActor.Num(); ++i)
	// {
	// 	AFloatingDamageTextActor* TextActor = ActiveTextActor[i];
	// 	const float distance = FVector::Dist(CameraLocation, TextActor->GetAnchorLocation());
	// 	const float verticalOffset = distance / (viewportSize.X / viewportScale);
	//
	// 	TextActor->SetActorLocation(TextActor->GetAnchorLocation() + FVector(0.0f,0.0f,i * verticalOffset * TextVerticalSpacing));
	// }
}

// void UTextComponent::ServerFloatingText_Implementation(FText text, FVector WorldLocation)
// {
// 	
// }

// void UTextComponent::ServerAddFloatingText_Implementation(FText text, FVector WorldLocation)
// {
// 	if (DamageTextClass == nullptr) return;
//
// 	const FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, WorldLocation + FVector(0.0f, 0.0f, TextVerticalOffset));
//
// 	AFloatingDamageTextActor* newTextActor = GetWorld()->SpawnActorDeferred<AFloatingDamageTextActor>(DamageTextClass, SpawnTransform, GetOwner());
// 	if (newTextActor == nullptr) return;
//
// 	newTextActor->Initialize(text);
// 	newTextActor->SetReplicates(true);
// 	newTextActor->OnDestroyed.AddDynamic(this, &UTextComponent::OnTextDestroyed);
// 	UGameplayStatics::FinishSpawningActor(newTextActor, SpawnTransform);
//
// 	ActiveTextActor.Insert(newTextActor, 0);
// }

// void UTextComponent::AddFloatingText_Implementation(FText text, FVector WorldLocation)
// {
// 	if(DamageTextClass == nullptr) return;
// 	
// 	const FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, WorldLocation +FVector(0.0f,0.0f,TextVerticalOffset));
// 	
// 	AFloatingDamageTextActor* newTextActor = GetWorld()->SpawnActorDeferred<AFloatingDamageTextActor>(DamageTextClass,SpawnTransform, GetOwner());
// 	if(newTextActor == nullptr) return;
// 	
// 	newTextActor->Initialize(text);
// 	newTextActor->SetReplicates(true);
// 	newTextActor->OnDestroyed.AddDynamic(this, &UTextComponent::OnTextDestroyed);
// 	UGameplayStatics::FinishSpawningActor(newTextActor, SpawnTransform);
//
// 	ActiveTextActor.Insert(newTextActor,0);
// }


void UTextComponent::OnTextDestroyed(AActor* DestroyedActor)
{
	ActiveTextActor.Pop();
}
