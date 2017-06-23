// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "UMGProject.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "BaseItem.h"
#include "UMGProjectCharacter.h"

//////////////////////////////////////////////////////////////////////////
// AUMGProjectCharacter

AUMGProjectCharacter::AUMGProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AUMGProjectCharacter::OnOverlapBegin);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	static ConstructorHelpers::FObjectFinder<UBlueprint> BP_Character(TEXT("Blueprint'/Game/Blueprints/EquipmentSetting/BP_EquiptCharacter.BP_EquiptCharacter'"));
	CharacterClass = BP_Character.Object->GeneratedClass;
}

void AUMGProjectCharacter::BeginPlay()
{
	Super::BeginPlay();

	Item = NewObject<UItemManager>(this);
	if (Item)
	{
		Item->Initialize(this);
	}
	EquipCharacter = GetWorld()->SpawnActor<AEquiptCharacter>(CharacterClass, FVector(-6883720.0f, -2559040.0f, -1614690.0f), FRotator::ZeroRotator);
	
} 

//////////////////////////////////////////////////////////////////////////
// Input

void AUMGProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AUMGProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUMGProjectCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AUMGProjectCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AUMGProjectCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AUMGProjectCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AUMGProjectCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AUMGProjectCharacter::OnResetVR);

	InputComponent->BindAction("PickUp", IE_Pressed, this, &AUMGProjectCharacter::PickUpItem);
	InputComponent->BindAction("Inventory", IE_Pressed, this, &AUMGProjectCharacter::ShowInventory);
	InputComponent->BindAction("Equipment", IE_Pressed, this, &AUMGProjectCharacter::ShowEquipment);
}

void AUMGProjectCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AUMGProjectCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AUMGProjectCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AUMGProjectCharacter::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	/*UE_LOG(LogClass, Warning, TEXT("Get Item0"));
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ABaseItem* GetItem = Cast<ABaseItem>(OtherActor);
		UE_LOG(LogClass, Warning, TEXT("Find Item"));
		if (GetItem)
		{
			UE_LOG(LogClass, Warning, TEXT("Get Item"));
			Item->GetItem(GetItem->ItemInfo);
			
		}
	}*/
}

void AUMGProjectCharacter::PickUpItem()
{
	if (IsPickUp)
	{
		ABaseItem* GetItem = Cast<ABaseItem>(ItemActor);
		if (GetItem) 
		{
			//UE_LOG(LogClass, Warning, TEXT("%s"), *GetItem->Mesh->GetName());
			ItemActor->Destroy();
			//ABaseItem* SpawnItem = GetWorld()->SpawnActor<ABaseItem>((UClass*)GetItem->ItemInfo.BPClass->GeneratedClass, GetActorLocation(), FRotator::ZeroRotator);
			Item->AddItem(GetItem->ItemInfo);
		}
	}
}

void AUMGProjectCharacter::ShowInventory()
{
	if (!Inventroy)
	{
		UE_LOG(LogClass, Warning, TEXT("인벤토리 클래스가 없습니다."));
		return;
	}
	
	APlayerController* MyController = GetWorld()->GetFirstPlayerController();

	if (!Item->IsInventory) {
		//Item->ShowItemToltip();
		Item->InventoryRef = CreateWidget<UUserWidget>(GetWorld(), Inventroy);
		Item->InventoryRef->AddToViewport();
		Item->IsInventory = true;
		MyController->bShowMouseCursor = true;
	}
	else
	{
		Item->InventoryRef->RemoveFromViewport();
		Item->IsInventory = false;
		MyController->bShowMouseCursor = false;
	}
		
}

void AUMGProjectCharacter::ShowEquipment()
{
	if (!Equipment)
	{
		UE_LOG(LogClass, Warning, TEXT("Equipment 클래스가 없습니다."));
		return;
	}

	APlayerController* MyController = GetWorld()->GetFirstPlayerController();
	if (!Item->IsEquipment)
	{
		Item->EquipmentRef = CreateWidget<UUserWidget>(GetWorld(), Equipment);
		Item->EquipmentRef->AddToViewport();
		Item->IsEquipment = true;
		MyController->bShowMouseCursor = true;
	}
	else
	{
		Item->EquipmentRef->RemoveFromViewport();
		Item->IsEquipment = false;
		MyController->bShowMouseCursor = false;
	}
}

void AUMGProjectCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AUMGProjectCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AUMGProjectCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AUMGProjectCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
