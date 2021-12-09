// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAM.generated.h"

class Grid;

UCLASS()
class PROCEDURALCAM_API ACAM : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACAM();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Function to apply cellular automata on our grid
	UFUNCTION(BlueprintCallable)
	virtual void CA(int32 InIterations);

public:	
	
	//The Grid which we create on beginplay
	TSharedPtr<Grid> TheGrid;
	
	//No of time we want to apply cellular automata
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 TotalIterations;

	/*
	* Starting location when considering a grid(Top left corner)
	* It's usually where we place the actor in the level but can be overriden in blueprints
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector StartLocation;

	//No of grids in X direction
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 GridSizeX;

	//No of grids in Y direction
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 GridSizeY;

	//Minimum no of grids in X direction that are considered a single cell
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CellMinX;

	//Minimum no of grids in Y direction that are considered a single cell
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CellMinY;

	//UnitLength of the each cell. It's multiplied by cellmin in both direction to get a cell's dimensions
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float UnitLength;

	//Spawn Parameters of both Meshes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector ScaleHorizontalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector ScaleVerticalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator RotHorizontalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator RotVerticalMesh;

	/*
	* Original grid cell orientation density before Applying Cellular automata.
	* 0 means all cells are vertical and 1 means all cells are horizontal
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float InitialCellDensity;

private:
	/*
	* Meshes to represent the orientation of each cell. We will be using instanced mesh for better performance
	*/
	USceneComponent* DefaultRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Room, meta = (AllowPrivateAccess = "true"))
		UInstancedStaticMeshComponent* HISMC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Room, meta = (AllowPrivateAccess = "true"))
		UInstancedStaticMeshComponent* VISMC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Room, meta = (AllowPrivateAccess = "true"))
		UStaticMesh* HorizontalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Room, meta = (AllowPrivateAccess = "true"))
		UStaticMesh* VerticalMesh;
};
