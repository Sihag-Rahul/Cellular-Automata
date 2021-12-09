#pragma once
#include "Cell.h"
#include "Grid.generated.h"

USTRUCT()
struct FGrid2DArray
{
	GENERATED_BODY()

public:
	TArray<TSharedPtr<Cell>> HG;

	//Operator [] is overriden to return it's associated data in the array
	TSharedPtr<Cell> operator[] (int32 i)
	{
		return HG[i];
	}

	void Add(TSharedPtr<Cell> A)
	{
		HG.Add(A);
	}
};

class Grid
{
public:
	Grid();
	Grid(UWorld* World, FVector InStartLoc, int32 InGridSizeX, int32 InGridSizeY, int32 InCellMinX, int32 InCellMinY, float InUnitLength, float InDensity);
	~Grid();

	void ApplyCA(UWorld* World, TArray<FGrid2DArray> InGrid, int32 iteration, int32 InGridSizeX, int32 InGridSizeY);

	FORCEINLINE TArray<FGrid2DArray> Get2DCellsGrid() const { return Grid2D; }

private:
	/*Container to hold our grid. We add more Grid2D inside to make it behave like a 2D array.
	* Second Array wil store our Cells.
	*/
	TArray<FGrid2DArray> Grid2D;
};