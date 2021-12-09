// Fill out your copyright notice in the Description page of Project Settings.


#include "CAM.h"
#include "Cell.h"
#include "Grid.h"

// Sets default values
ACAM::ACAM()
{
 	// Turned tick off
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	SetRootComponent(DefaultRoot);
	DefaultRoot->SetMobility(EComponentMobility::Static);
	
	//Instanced Static mesh, We created two of them for visual representation of different cells
	HISMC = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("HISMC"));
	HISMC->SetMobility(EComponentMobility::Static);
	HISMC->SetCollisionProfileName("BlockAll");
	HISMC->SetStaticMesh(HorizontalMesh);

	VISMC = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("VISMC"));
	VISMC->SetMobility(EComponentMobility::Static);
	VISMC->SetCollisionProfileName("BlockAll");
	VISMC->SetStaticMesh(VerticalMesh);

	//Default Values, Can be changed in Blueprints
	StartLocation = GetActorLocation();
	GridSizeX = 50;
	GridSizeY = 50;
	CellMinX = 1;
	CellMinY = 1;
	UnitLength = 200.f;
	InitialCellDensity = 0.4f;
	TotalIterations = 4;
	ScaleHorizontalMesh = FVector(0.5f, 0.5f, 1.f);
	ScaleVerticalMesh = FVector(0.5f, 0.5f, 1.f);
	RotHorizontalMesh = FRotator(0.f);
	RotVerticalMesh = FRotator(0.f);

}

// Called when the game starts or when spawned
void ACAM::BeginPlay()
{
	Super::BeginPlay();
	
	//Creating a new grid. using TSharedPtr so that we don't need to worry about memory, it removes itself
	TSharedPtr<Grid> TempGrid(new Grid(GetWorld(), StartLocation, GridSizeX, GridSizeY, CellMinX, CellMinY, UnitLength, InitialCellDensity));
	TheGrid = TempGrid;

	//We are calling it by default in beginplay, can be called in blueprints
	CA(TotalIterations);
}

void ACAM::CA(int32 InIterations)
{
	TheGrid->ApplyCA(GetWorld(), TheGrid->Get2DCellsGrid(), InIterations, GridSizeX, GridSizeY);
	
	/*
	Iterating over all of the cells created after cellular automata and spawn a mesh for visual representation of their orientation
	*/
	for (int32 i = 0; i < GridSizeX; i++)
	{
		for (int32 j = 0; j < GridSizeX; j++)
		{
			
			TArray<FGrid2DArray> TempGrid2D = TheGrid->Get2DCellsGrid();

			ECellOrientation CellOrient = TempGrid2D[i][j]->GetCellOrientation();
			FVector Loc(((TempGrid2D[i][j]->GetCornerCoords().LRX) - ((CellMinX * UnitLength) / 2)),
						((TempGrid2D[i][j]->GetCornerCoords().LRY) - ((CellMinX * UnitLength) / 2)),  0.f);
			
			if (CellOrient == ECellOrientation::ECO_Horizontal)
			{
				FTransform InstanceTransform(RotHorizontalMesh, Loc, ScaleHorizontalMesh);
				HISMC->AddInstance(InstanceTransform);
				UE_LOG(LogTemp, Warning, TEXT("Horizontal Mesh Instance Created."));
			}
			else
			{
				FTransform InstanceTransform(RotVerticalMesh, Loc, ScaleVerticalMesh);
				VISMC->AddInstance(InstanceTransform);
				UE_LOG(LogTemp, Warning, TEXT("Vertical Mesh Instance Created."));
			}
		}
	}
}