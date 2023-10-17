#include "Weapon/BulletHole.h"

#include "Components/DecalComponent.h"

ABulletHole::ABulletHole()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComponent"));
	DecalComponent->SetIsReplicated(true);
	SetRootComponent(DecalComponent);

	DecalComponent->FadeDuration = 3;
	DecalComponent->FadeStartDelay = 1;
}
void ABulletHole::BeginPlay()
{
	Super::BeginPlay();
	
}

