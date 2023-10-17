#include "HUD/OverheadWidget.h"
#include "Components/TextBlock.h"

void UOverheadWidget::SetDisplayText(FString TextToDisplay)
{
	if (DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
}

void UOverheadWidget::ShowPlayerNetRole(APawn* InPawn)
{
	ENetRole RemoteRole = InPawn->GetRemoteRole();
	ENetRole LocalRole = InPawn->GetLocalRole();
	FString Remote_Role;
	switch (RemoteRole)
	{
	case ENetRole::ROLE_Authority:
		Remote_Role = FString("Authority");
		break;
	case ENetRole::ROLE_AutonomousProxy:
		Remote_Role = FString("Autonomous Proxy");
		break;
	case ENetRole::ROLE_SimulatedProxy:
		Remote_Role = FString("Simulated Proxy");
		break;
	case ENetRole::ROLE_None:
		Remote_Role = FString("None");
		break;
	}

	FString Local_Role;
	switch (LocalRole)
	{
	case ENetRole::ROLE_Authority:
		Local_Role = FString("Authority");
		break;
	case ENetRole::ROLE_AutonomousProxy:
		Local_Role = FString("Autonomous Proxy");
		break;
	case ENetRole::ROLE_SimulatedProxy:
		Local_Role = FString("Simulated Proxy");
		break;
	case ENetRole::ROLE_None:
		Local_Role = FString("None");
		break;
	}
	FString LocalRoleString = FString::Printf(TEXT("Local : %s"), *Local_Role);
	FString RemoteRoleString = FString::Printf(TEXT("Remote : %s"), *Remote_Role);
	SetDisplayText(RemoteRoleString);
}

void UOverheadWidget::NativeDestruct()
{
	RemoveFromParent();
	Super::NativeDestruct();
}
