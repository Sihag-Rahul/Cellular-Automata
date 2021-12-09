#include "Grid.h"
#include "Cell.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"

Grid::Grid()
{
	UE_LOG(LogTemp, Warning, TEXT("Grid Created."));
}

Grid::Grid(UWorld* World, FVector InStartLoc, int32 InGridSizeX, int32 InGridSizeY, int32 InCellMinX, int32 InCellMinY, float InUnitLength, float InDensity)
{
	/*
	Add total arrays equal to GridSizeX so that each of them can be used to store all the cells of their columns
	*/
	for (int32 j = 0; j < InGridSizeX; j++)
	{
		Grid2D.Add(FGrid2DArray());
	}

	for (int32 j = 0; j < InGridSizeX; j++)
	{
		for (int32 k = 0; k < InGridSizeY; k++)
		{
			FCornerCoords CurrentCellCornerCoords;
			CurrentCellCornerCoords.ULX = InStartLoc.X + ((j) * (InCellMinX * InUnitLength));
			CurrentCellCornerCoords.ULY = InStartLoc.Y + ((k) * (InCellMinY * InUnitLength));
			CurrentCellCornerCoords.LRX = InStartLoc.X + ((j+1) * (InCellMinX * InUnitLength));
			CurrentCellCornerCoords.LRY = InStartLoc.Y + ((k+1) * (InCellMinY * InUnitLength));

			ECellOrientation CurrentCellOrientation = ECellOrientation::ECO_Vertical;
			bool Rand = UKismetMathLibrary::RandomBoolWithWeight(InDensity);
			if (Rand)
			{
				CurrentCellOrientation = ECellOrientation::ECO_Horizontal;
			}
			else
			{
				CurrentCellOrientation = ECellOrientation::ECO_Vertical;
			}
			
			TSharedPtr<Cell> A(new Cell(CurrentCellCornerCoords, CurrentCellOrientation));

			Grid2D[j].Add(A);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Grid Created."));
}

Grid::~Grid()
{
	UE_LOG(LogTemp, Warning, TEXT("Grid Destroyed."));
}

void Grid::ApplyCA(UWorld* World, TArray<FGrid2DArray> InGrid, int32 iteration, int32 InGridSizeX, int32 InGridSizeY)
{
	for (int32 i = 0; i < iteration; i++)
	{
		for (int32 j = 0; j < InGridSizeX; j++)
		{
			for (int32 k = 0; k < InGridSizeY; k++)
			{
				int32 Count = 0;
				for (int32 x = j - 1; x <= j + 1; x++)
				{
					for (int32 y = k - 1; y <= k + 1; y++)
					{
						//Iterating over all the neightbours
						if (InGrid.IsValidIndex(x) && Grid2D.IsValidIndex(y))
						{
							if (x != j || y != k)		//Our cell itseld isn't considered when checking for neighbours
							{
								if (InGrid[x][y]->GetCellOrientation() == ECellOrientation::ECO_Vertical)
								{
									Count++;
								}
							}
						}
						else
						{
							//If the neighbour doesn't exist, we consider it as vertical by default
							Count++;
						}
					}
				}

				//Setting the rules for Cellular Automate, Can be changed to get different results
				if (Count > 4)
				{
					InGrid[j][k]->SetCellOrientation(ECellOrientation::ECO_Vertical);
				}
				else
				{
					InGrid[j][k]->SetCellOrientation(ECellOrientation::ECO_Horizontal);
				}
			}
		}
	}
}