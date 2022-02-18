#include "VRalsPlayerController.h"

#include "VRBasePlayer.h"
#include "Character/ALSPlayerCameraManager.h"
#include "Components/ALSDebugComponent.h"
#include "Kismet/GameplayStatics.h"

void AVRalsPlayerController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);
	PossessedCharacter = Cast<AVRBasePlayer>(NewPawn);
	if (!IsRunningDedicatedServer())
	{
		// Servers want to setup camera only in listen servers.
		SetupCamera();
	}
	SetupDebugInputs();
}

void AVRalsPlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();
	PossessedCharacter = Cast<AVRBasePlayer>(GetPawn());
	SetupCamera();
}

void AVRalsPlayerController::BeginPlayingState()
{
	Super::BeginPlayingState();
	if (GetLocalRole() == ROLE_AutonomousProxy)
	{
		SetupDebugInputs();
	}
}

void AVRalsPlayerController::SetupCamera()
{
	// Call "OnPossess" in Player Camera Manager when possessing a pawn
	AALSPlayerCameraManager* CastedMgr = Cast<AALSPlayerCameraManager>(PlayerCameraManager);
	if (PossessedCharacter && CastedMgr)
	{
		//ТУТ
		//CastedMgr->OnPossess(PossessedCharacter);
	}
}

void AVRalsPlayerController::SetupDebugInputs()
{
	// Bind inputs for debugging
	if (PossessedCharacter)
	{
		UActorComponent* Comp = PossessedCharacter->GetComponentByClass(UALSDebugComponent::StaticClass());
		if (Comp)
		{
			UALSDebugComponent* DebugComp = Cast<UALSDebugComponent>(Comp);
			if (InputComponent && DebugComp)
			{
				InputComponent->BindKey(EKeys::Tab, EInputEvent::IE_Pressed, DebugComp, &UALSDebugComponent::ToggleHud);
				InputComponent->BindKey(EKeys::V, EInputEvent::IE_Pressed, DebugComp, &UALSDebugComponent::ToggleDebugView);
				InputComponent->BindKey(EKeys::T, EInputEvent::IE_Pressed, DebugComp, &UALSDebugComponent::ToggleTraces);
				InputComponent->BindKey(EKeys::Y, EInputEvent::IE_Pressed, DebugComp, &UALSDebugComponent::ToggleDebugShapes);
				InputComponent->BindKey(EKeys::U, EInputEvent::IE_Pressed, DebugComp, &UALSDebugComponent::ToggleLayerColors);
				InputComponent->BindKey(EKeys::I, EInputEvent::IE_Pressed, DebugComp, &UALSDebugComponent::ToggleCharacterInfo);
				InputComponent->BindKey(EKeys::Z, EInputEvent::IE_Pressed, DebugComp, &UALSDebugComponent::ToggleSlomo);
				InputComponent->BindKey(EKeys::Comma, EInputEvent::IE_Pressed, DebugComp, &UALSDebugComponent::PreviousFocusedDebugCharacter);
				InputComponent->BindKey(EKeys::Period, EInputEvent::IE_Pressed, DebugComp, &UALSDebugComponent::NextFocusedDebugCharacter);
				InputComponent->BindKey(EKeys::M, EInputEvent::IE_Pressed, DebugComp, &UALSDebugComponent::ToggleDebugMesh);
			}
		}
	}
}
