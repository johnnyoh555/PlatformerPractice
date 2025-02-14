// Fill out your copyright notice in the Description page of Project Settings.


#include "PFCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PFCharacterControlData.h"
#include "Components/TextBlock.h"
#include "CharacterStat/PFCharacterStatComponent.h"
#include "UI/PFWidgetComponent.h"
#include "UI/PFCoinDisplayWidget.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "Interface/PFRestartInterface.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APFCharacter::APFCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	// Pawn
	/*bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;*/

	// Capsule
	GetCapsuleComponent()->InitCapsuleSize(40.f, 80.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
	GetCapsuleComponent()->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));

	// Movement
	/*GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;*/

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/StackOBot/Characters/Bot/Mesh/SKM_Bot.SKM_Bot'"));
	if (CharacterMeshRef.Object)
	{
		UE_LOG(LogTemp, Log, TEXT("Skeletal"));
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}
	
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/PF/Animation/ABP_PFCharacter.ABP_PFCharacter_C"));
	if (AnimInstanceClassRef.Class)
	{
		UE_LOG(LogTemp, Log, TEXT("AnimInstance"));
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}
	/*PrimaryActorTick.bCanEverTick = true;*/

	// Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -78.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));

	// Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	/*CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;*/

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Input
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/PF/Input/IMC_PFCharacter.IMC_PFCharacter'"));
	if (nullptr != InputMappingContextRef.Object)
	{
		DefaultMappingContext = InputMappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PF/Input/Action/IA_Move.IA_Move'"));
	if (nullptr != InputActionMoveRef.Object)
	{
		MoveAction = InputActionMoveRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PF/Input/Action/IA_Jump.IA_Jump'"));
	if (nullptr != InputActionJumpRef.Object)
	{
		JumpAction = InputActionJumpRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PF/Input/Action/IA_Look.IA_Look'"));
	if (nullptr != InputActionLookRef.Object)
	{
		LookAction = InputActionLookRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionRunRef(TEXT("/Script/EnhancedInput.InputAction'/Game/PF/Input/Action/IA_Run.IA_Run'"));
	if (nullptr != InputActionRunRef.Object)
	{
		RunAction = InputActionRunRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UPFCharacterControlData> CharacterDataRef(TEXT("/Script/PlatformerPRACTICE.PFCharacterControlData'/Game/PF/CharacterControl/ABC_Shoulder.ABC_Shoulder'"));
	if (CharacterDataRef.Object)
	{
		CharacterControlManager = CharacterDataRef.Object;
	}

	// Stat Component
	Stat = CreateDefaultSubobject<UPFCharacterStatComponent>(TEXT("Stat"));

	// Widget Component
	CoinScore = CreateDefaultSubobject<UPFWidgetComponent>(TEXT("Widget"));
	CoinScore->SetupAttachment(GetMesh());
	CoinScore->SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f));

	static ConstructorHelpers::FClassFinder<UUserWidget>  CoinDisplayWidgetRef(TEXT("/Game/PF/UI/WBP_CoinDisplay.WBP_CoinDisplay_C"));
	if (CoinDisplayWidgetRef.Class)
	{
		CoinScore->SetWidgetClass(CoinDisplayWidgetRef.Class);
		CoinScore->SetWidgetSpace(EWidgetSpace::Screen);
		CoinScore->SetDrawSize(FVector2D(200.0f, 50.0f));
		CoinScore->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem>  RespawnEffectRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/StackOBot/FX/SpawnPadActive/FX_SpawnPadActive.FX_SpawnPadActive'"));
	if (RespawnEffectRef.Object)
	{
		RespawnEffect = RespawnEffectRef.Object;
	}

	// 초기 스케일 설정 (투명 상태처럼 보이게)
	SetActorScale3D(FVector::ZeroVector);

	// 메쉬 가시성 끄기
	/*if (GetMesh())
	{
		GetMesh()->SetVisibility(false);
	}*/

	Tags.Add(TEXT("Player")); // 플레이어 태그 추가
}

// Called when the game starts or when spawned
void APFCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetCharacterControlData(CharacterControlManager);

	if (APlayerController* PlayerController = CastChecked<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	StartSpawnEffect();
	//if (RespawnEffect)
	//{
	//	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
	//		GetWorld(),                      // 현재 월드
	//		RespawnEffect,                   // Niagara System
	//		GetActorLocation(),              // 스폰 위치 (캐릭터 위치)
	//		GetActorRotation()               // 스폰 회전 (캐릭터 회전)
	//	);
	//}
}

// Called to bind functionality to input
void APFCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APFCharacter::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APFCharacter::Look);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APFCharacter::Jump); 
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APFCharacter::StopJumping);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &APFCharacter::StartRunning);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Canceled, this, &APFCharacter::StopRunning);
}

void APFCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.X);
		AddMovementInput(RightDirection, MovementVector.Y);
	}
}

void APFCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void APFCharacter::SetCharacterControlData(const UPFCharacterControlData* CharacterControlData)
{
	// Pawn
	bUseControllerRotationYaw = CharacterControlData->bUseControllerRotationYaw;

	// Character
	GetCharacterMovement()->bOrientRotationToMovement = CharacterControlData->bOrientRotationToMovement;
	GetCharacterMovement()->bUseControllerDesiredRotation = CharacterControlData->bUseControllerDesiredRotation;
	GetCharacterMovement()->RotationRate = CharacterControlData->RotationRate;
	GetCharacterMovement()->JumpZVelocity = CharacterControlData->JumpZVelocity;
	GetCharacterMovement()->AirControl = CharacterControlData->AirControl;
	GetCharacterMovement()->MaxWalkSpeed = CharacterControlData->MaxWalkSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = CharacterControlData->MinAnalogWalkSpeed;
	GetCharacterMovement()->BrakingDecelerationWalking = CharacterControlData->BrakingDecelerationWalking;
	GetCharacterMovement()->GravityScale = CharacterControlData->GravityScale;

	CameraBoom->TargetArmLength = CharacterControlData->TargetArmLength;
	CameraBoom->SetRelativeRotation(CharacterControlData->RelativeRotation);
	CameraBoom->bUsePawnControlRotation = CharacterControlData->bUsePawnControlRotation;
	CameraBoom->bInheritPitch = CharacterControlData->bInheritPitch;
	CameraBoom->bInheritYaw = CharacterControlData->bInheritYaw;
	CameraBoom->bInheritRoll = CharacterControlData->bInheritRoll;
	CameraBoom->bDoCollisionTest = CharacterControlData->bDoCollisionTest;

	WalkSpeed = CharacterControlData->WalkSpeed;
	RunSpeed = CharacterControlData->RunSpeed;
}

void APFCharacter::StartRunning()
{
	if (GetCharacterMovement()->IsFalling())
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot run while jumping"));
		bWantsToRun = true; // 공중에서는 달리기 요청을 저장
		return;
	}

	bWantsToRun = true;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	UE_LOG(LogTemp, Log, TEXT("Running Started"));
}

void APFCharacter::StopRunning()
{
	bWantsToRun = false;

	if (GetCharacterMovement()->IsFalling())
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot stop running while jumping"));
		return;
	}

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	UE_LOG(LogTemp, Log, TEXT("Running Stopped"));
}

void APFCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (bWantsToRun)
	{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

void APFCharacter::SetupCharacterWidget(UPFUserWidget* InUserWidget)
{
	UPFCoinDisplayWidget* CoinDisplayWidget = Cast<UPFCoinDisplayWidget>(InUserWidget);
	if (CoinDisplayWidget)
	{
		CoinDisplayWidget->UpdateCoinScore(Stat->GetCurrentCoin(), 0);
		Stat->OnCoinChanged.AddUObject(CoinDisplayWidget, &UPFCoinDisplayWidget::UpdateCoinScore);
	}
}

void APFCharacter::TakeCoin()
{
	Stat->AddCoin();
}

void APFCharacter::StartSpawnEffect()
{
	// 초기화: 메쉬를 보이지 않도록 설정
	//GetMesh()->SetVisibility(false);

	// 타이머로 스케일과 머티리얼 파라미터 점진적으로 증가
	GetWorld()->GetTimerManager().SetTimer(MaterialTimerHandle, this, &APFCharacter::UpdateSpawnEffect, 0.01f, true);
}

void APFCharacter::UpdateSpawnEffect()
{
	FVector CurrentScale = GetActorScale3D();
	FVector TargetScale = FVector(1.0f, 1.0f, 1.0f); // 최종 크기

	// 스케일 증가
	CurrentScale += FVector(0.01f, 0.01f, 0.01f);
	SetActorScale3D(CurrentScale);

	// 스폰 효과 완료
	if (CurrentScale.GetMax() >= TargetScale.GetMax())
	{
		SetActorScale3D(TargetScale); // 최종 크기 설정
		//GetMesh()->SetVisibility(true); // 메쉬 보이기
		GetWorld()->GetTimerManager().ClearTimer(MaterialTimerHandle);
	}
}

void APFCharacter::TriggerRestart()
{
	// GameMode에서 RestartInterface 구현 여부 확인
	IPFRestartInterface* RestartInterface = Cast<IPFRestartInterface>(GetWorld()->GetAuthGameMode());
	if (RestartInterface)
	{
		RestartInterface->RestartStage();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GameMode does not implement RestartInterface!"));
	}
}

void APFCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Kill Z 체크
	if (GetActorLocation().Z < -1000.0f) // Kill Z 값
	{
		TriggerRestart();
	}
}

void APFCharacter::ShrinkBeforeTeleport()
{
	FVector TargetScale(0.1f, 0.1f, 0.1f);
	float ShrinkDuration = 1.0f;

	FVector StartScale = GetActorScale3D();
	float ShrinkStartTime = GetWorld()->GetTimeSeconds();

	TWeakObjectPtr<APFCharacter> WeakThis(this);

	GetWorldTimerManager().SetTimer(ShrinkTimer, [WeakThis, StartScale, TargetScale, ShrinkDuration, ShrinkStartTime]() mutable
	{
		if (!WeakThis.IsValid())
		{
			return;
		}

		APFCharacter* Character = WeakThis.Get();

		float CurrentTime = Character->GetWorld()->GetTimeSeconds();
		float Alpha = FMath::Clamp((CurrentTime - ShrinkStartTime) / ShrinkDuration, 0.0f, 1.0f);
		FVector NewScale = FMath::Lerp(StartScale, TargetScale, Alpha);

		Character->SetActorScale3D(NewScale);

		if (Alpha >= 1.0f)
		{
			Character->GetWorldTimerManager().ClearTimer(Character->ShrinkTimer); // 클래스 멤버 접근
			Character->TeleportToNextStage();
		}
	}, 0.02f, true);
}

void APFCharacter::TeleportToNextStage()
{
	// 새로운 레벨 로드
	UGameplayStatics::OpenLevel(this, FName("Step2"));
}

void APFCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(ShrinkTimer); // 타이머 정리
	Super::EndPlay(EndPlayReason);
}