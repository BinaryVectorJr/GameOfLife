#include <raylib.h>
#include "grid.hpp"

void Grid::DrawGrid()
{
	// Looking through all the cells in the grid
	for (int row = 0; row < gridRows; row++)
	{
		for (int col = 0; col < gridColumns; col++)
		{
			// Color variable to hold the color of the cell (ternary operator); GREEN (1) = alive, GREY (0) = dead
			Color cellColor = gridCells[row][col] ? Color{ 0, 255, 0, 255 } : Color{ 55,55,55,255 };

			// Drawing a square using raylib's grid function 
			// Multiply with size of cell to scale it down to proper dimensions
			// The gridCellSize - 1 makes it 1 pixel less in cell width and cell height, so we can sim "grid lines"
			DrawRectangle(col * gridCellSize, row * gridCellSize, gridCellSize - 1, gridCellSize - 1, cellColor);
		}
	}
}

void Grid::SetCellValue(int cellRowInGrid, int cellColumnInGrid, int valueInGrid)
{
	// Check to see if row and column values are within limits
	if(IsCellWithinGridBounds(cellRowInGrid, cellColumnInGrid))
	{
		gridCells[cellRowInGrid][cellColumnInGrid] = valueInGrid;
	}

}

int Grid::GetCellValue(int cellRowInGrid, int cellColumnInGrid)
{
	// Check to see if row and column values are within limits
	if (IsCellWithinGridBounds(cellRowInGrid, cellColumnInGrid))
	{
		return gridCells[cellRowInGrid][cellColumnInGrid];
	}
	return 0;

}

bool Grid::IsCellWithinGridBounds(int cellRowInGrid, int cellColumnInGrid)
{
	if (cellRowInGrid >= 0 && cellRowInGrid < gridRows && cellColumnInGrid >= 0 && cellColumnInGrid < gridColumns)
	{
		return true;
	}
	return false;
}

void Grid::FillGridRandomly()
{
	// Checking each cell in current grid one by one
	// TODO: This can also be made faster maybe using multithreading or parallel processing
	for (int currentRow = 0; currentRow < gridRows; currentRow++)
	{
		for (int currentCol = 0; currentCol < gridColumns; currentCol++)
		{
			// Random assignment of value (Random function of Raylib)
			// Cannot just do (0,1) since that is a 50-50 distribution
			// So we skew the percentage of 1 (20%) so that there are more 0s than 1s for a more optimal behavior
			int randomCellValue = GetRandomValue(0, 4);								// Valid values are 0,1,2,3,4
			gridCells[currentRow][currentCol] = (randomCellValue == 4) ? 1 : 0;		// Chance to get 4 is 1/5
		}
	}

}

void Grid::ClearGrid()
{
	// Checking each cell in current grid one by one
	for (int currentRow = 0; currentRow < gridRows; currentRow++)
	{
		for (int currentCol = 0; currentCol < gridColumns; currentCol++)
		{
			gridCells[currentRow][currentCol] = 0;
		}
	}
}

void Grid::ToggleGridCell(int cellRowInGrid, int cellColumnInGrid)
{
	if (IsCellWithinGridBounds(cellRowInGrid, cellColumnInGrid))
	{
		// Have to use "~" which is bitwise NOT insted of "!"
		gridCells[cellRowInGrid][cellColumnInGrid] = ~gridCells[cellRowInGrid][cellColumnInGrid];
	}
}
