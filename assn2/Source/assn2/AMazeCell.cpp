// Fill out your copyright notice in the Description page of Project Settings.
#pragma optimize("", off)

#include "AMazeCell.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstance.h" 
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AMazeCell::AMazeCell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Engine/BasicShapes/Plane"));
	StaticMesh = MeshRef.Object;
	check(StaticMesh != nullptr);
	

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialRef(TEXT("Material'/Game/WallMaterial.WallMaterial'"));
	Material = MaterialRef.Object;
	check(Material != nullptr);

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"), true);
	check(SceneComponent != nullptr);
	this->RootComponent = SceneComponent;
}

// Called when the game starts or when spawned
void AMazeCell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMazeCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMazeCell::EnableWall(Wall wall, int tileSize)
{
	auto m = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), TEXT("Wall " + wall), RF_Transactional);
	this->WallComponents[wall] = m;

	m->SetStaticMesh(StaticMesh);
	//m->SetMobility(EComponentMobility::Movable);
	m->SetupAttachment(RootComponent);
	m->CreateAndSetMaterialInstanceDynamicFromMaterial(0, Material);
	m->RegisterComponent();

	m->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	m->SetCollisionResponseToAllChannels(ECR_Ignore);
	m->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	switch (wall) {
		case Wall::North: {
			m->SetRelativeLocation(FVector(tileSize / 2.0f, 0.0f, tileSize / 2.0f));
			FQuat rot = FQuat::MakeFromEuler(FVector(90.0f, 0.0f, 90.0f));
			m->AddRelativeRotation(rot);
			break;
		}
		case Wall::East: {
			m->SetRelativeLocation(FVector(0.0f, tileSize / 2.0f, tileSize / 2.0f));
			FQuat rot = FQuat::MakeFromEuler(FVector(90.0f, 0.0f, 0.0f));
			break;
		}
		case Wall::South: {
			m->SetRelativeLocation(FVector(-tileSize / 2.0f, 0.0f, tileSize / 2.0f));
			FQuat rot = FQuat::MakeFromEuler(FVector(90.0f, 0.0f, 90.0f));
			break;
		}
		case Wall::West: {
			m->SetRelativeLocation(FVector(0.0f, -tileSize / 2.0f, tileSize / 2.0f));
			FQuat rot = FQuat::MakeFromEuler(FVector(90.0f, 0.0f, 0.0f));
			m->AddRelativeRotation(rot);
			break;
		}
	}

	/*m->SetGenerateOverlapEvents(false);
	m->SetCanEverAffectNavigation(false);
	m->bCastDynamicShadow = false;
	m->bCastStaticShadow = false;
	m->bAffectDistanceFieldLighting = false;
	m->bAffectDynamicIndirectLighting = false;*/

}
