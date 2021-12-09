#pragma once

//Scoped Enum, Enum classes do not implicitly convert to other types
enum class ECellOrientation
{
	ECO_Horizontal,
	ECO_Vertical
};

struct FCornerCoords	//On a rectangle We only need ends of any Diagonal to know all the points in between.
{
	int32 ULX;			//ULX is Upper Left Corner's X coordinate.
	int32 ULY;			//ULY is Upper Left Corner's Y coordinate.
	int32 LRX;			//ULX is Lower Right Corner's X coordinate.
	int32 LRY;			//ULY is Lower Right Corner's Y coordinate.
};

class Cell
{
public:
	Cell();
	Cell(const FCornerCoords& InCoordinates, const ECellOrientation& InCellOrientation);
	~Cell();

	//Getters and Setters for our private variables
	FORCEINLINE FCornerCoords GetCornerCoords() const { return CornerCoords; }
	FORCEINLINE void SetCornerCoords(FCornerCoords InCoords) { CornerCoords = InCoords; }

	FORCEINLINE ECellOrientation GetCellOrientation() const { return CellOrientation; }
	FORCEINLINE void SetCellOrientation(ECellOrientation InCellOrientation) { CellOrientation = InCellOrientation; }

	FORCEINLINE static int32 GetCellCount() { return CellCount; }

private:

	FCornerCoords CornerCoords;
	ECellOrientation CellOrientation;

	//To keep track of total runtime cell count, Static makes sure we can access it at all times
	static int32 CellCount;
};