
#pragma once

#include "CoreMinimal.h"
#include "VRPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "VRalsPlayerController.generated.h"

class AVRBasePlayer;

/**
 * Player controller class
 */
UCLASS(Blueprintable, BlueprintType)
class UNNAMEDVR_API AVRalsPlayerController : public AVRPlayerController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* NewPawn) override;

	virtual void OnRep_Pawn() override;

	virtual void BeginPlayingState() override;

private:
	void SetupCamera();

	void SetupDebugInputs();
	
public:
	/** Main character reference */
	UPROPERTY(BlueprintReadOnly, Category = "VR Player Controller")
	AVRBasePlayer* PossessedCharacter = nullptr;
};
