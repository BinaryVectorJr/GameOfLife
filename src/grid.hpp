#pragma once // Ensures this header file is only included once to avoid duplicate definitions
#include <vector>

// Current purposes we will use Toroidal grid (grid where cells on leftmost edge have the cells on the rightmost edge as their neighbors; similarly top-bottom; continuous grid
class Grid
{
private:
	int gridRows;
	int gridColumns;
	int gridCellSize;

	// Representing grid as a vector of vectors (2D)
	// Represent each cell as int; gives us flexibility to add more states if we want to make it complex
	std::vector<std::vector<int>> gridCells;

public:
	// Constructor with initialized values using an initializer list
	Grid(int winWidth, int winHeight, int cellSize): 
		gridRows(winHeight/cellSize), 
		gridColumns(winWidth/cellSize), 
		gridCellSize(cellSize), 
		gridCells(gridRows, std::vector<int>(gridColumns,0)){}; // Initializes the cells as row vectors containing column vectors; each column vector has one value and is initialzed to 0 (a.k.a. dead state)

	// Drawing the grid
	void DrawGrid();

	// Function to access a grid cell (value setter)
	void SetCellValue(int cellRowInGrid, int cellColumnInGrid, int value);

	// Function to get the value of a cell
	int GetCellValue(int cellRowInGrid, int cellColumnInGrid);

	// Check for row and column validity
	bool IsCellWithinGridBounds(int cellRowInGrid, int cellColumnInGrid);

	// Get total rows in current grid
	int GetTotalGridRows() { return gridRows; }

	// Get total columns in current grid
	int GetTotalGridColumns() { return gridColumns; }

	// Filling the grid with values randomly for starting state
	void FillGridRandomly();

	// Clearing the grid
	void ClearGrid();

	// To toggle the value of a cell (for mouse click events)
	void ToggleGridCell(int cellRowInGrid, int cellColumnInGrid);
};
