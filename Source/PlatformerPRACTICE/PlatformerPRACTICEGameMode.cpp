// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlatformerPRACTICEGameMode.h"
#include "PlatformerPRACTICECharacter.h"
#include "UObject/ConstructorHelpers.h"

APlatformerPRACTICEGameMode::APlatformerPRACTICEGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
