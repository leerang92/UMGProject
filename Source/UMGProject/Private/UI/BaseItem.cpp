// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGProject.h"
#include "BaseItem.h"


// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereColl = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereColl->SetSphereRadius(200.0f);
	RootComponent = SphereColl;

	Mesh = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	Mesh->AttachTo(SphereColl);

}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

