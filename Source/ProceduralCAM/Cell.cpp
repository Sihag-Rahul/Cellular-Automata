#include "Cell.h"

int32 Cell::CellCount = 0;

Cell::Cell()
{
	++CellCount;
	UE_LOG(LogTemp, Warning, TEXT("Cell Created."));
}

Cell::Cell(const FCornerCoords& Coordinates, const ECellOrientation& InCellOrientation)
{
	
	//Set the Corner values
	CornerCoords.ULX = Coordinates.ULX;
	CornerCoords.ULY = Coordinates.ULY;
	CornerCoords.LRX = Coordinates.LRX;
	CornerCoords.LRY = Coordinates.LRY;

	//Set the Orientation
	if (InCellOrientation == ECellOrientation::ECO_Horizontal)
	{
		CellOrientation = ECellOrientation::ECO_Horizontal;
	}
	else
	{
		CellOrientation = ECellOrientation::ECO_Vertical;
	}

	++CellCount;
	UE_LOG(LogTemp, Warning, TEXT("Cell Created."));
}

Cell::~Cell()
{
	--CellCount;
	UE_LOG(LogTemp, Warning, TEXT("Cell Destroyed."));
}