// Fill out your copyright notice in the Description page of Project Settings.

#include "UMGProject.h"
#include "EquiptCharacter.h"


// Sets default values
AEquiptCharacter::AEquiptCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh Component"));
	RootComponent = Mesh;

}

// Called when the game starts or when spawned
void AEquiptCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEquiptCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

