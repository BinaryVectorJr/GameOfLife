#include <vector>
#include <utility>
#include "simulationManager.hpp"

void SimulationManager::DrawGridInSim()
{
	gameGrid.DrawGrid();
}

void SimulationManager::SetCellValueInSim(int cellRowInSim, int cellColumnInSim, int valueInSim)
{
	gameGrid.SetCellValue(cellRowInSim, cellColumnInSim, valueInSim);
}

int SimulationManager::CountAliveNeighborsInSim(int cellRowInSim, int cellColumnInSim)
{
	// Initialize variable to store results of neighbors that are alive
	int currentAliveNeighbors = 0;

	// Using vector of Pair data type to keep track of offset pairs of all neighbors (Moore Neighbors)
	std::vector<std::pair<int, int>> neighborOffsets = {
		{-1,0},		// NORTH (up)
		{1,0},		// SOUTH (down)
		{0,-1},		// WEST (left)
		{0,1},		// EAST (right)
		{-1,-1},	// NORTH-WEST (diag. up-left)
		{-1,1},		// NORTH-EAST (diag. up-right)
		{1,-1},		// SOUTH-WEST (diag. lo-left)
		{1,1}		// SOUTH EAST (diag. lo-right
	};

	// Ranged for loop to iterate through vector of offsets, and add the offset to the value of the currently alive cell being checked
	for (const auto& offset : neighborOffsets)
	{
		//// Original calculation but can cause crashes when the grid edges are referenced
		//int neighborRow = cellRowInSim + offset.first;
		//int neighborCol = cellColumnInSim + offset.second;

		// Modified calculation for a Toroidal grid - a grid that is continuous and the last row (or col) references the first as its neighbor (and vice versa)
		// Eg: Modulo Arithmetic: (row + offset + totalRows) mod totalRows
		// E.g. cell[5][29] (right edge) + {0,1} = cell[(5+0+30)%30][(29+1+30)%30] in a 30x30 grid gives newcell[5][0] (left edge)
		// E.g. cell[5][0] (left edge) + {0,-1} = cell[(5+0+30)%30][(0-1+30)%30] in a 30x30 grid gives newcell[5][29] (right edge)
		int neighborRow = (cellRowInSim + offset.first + gameGrid.GetTotalGridRows()) % gameGrid.GetTotalGridRows();
		int neighborCol = (cellColumnInSim + offset.second + gameGrid.GetTotalGridColumns()) % gameGrid.GetTotalGridColumns();

		// Adding the values of all the neigboring cells together
		// Since they are 1 or 0, adding them will give total no. of alive neighbors
		// Drawback - This only works if alive is represented as 1 and dead is 0; TODO: Make compatible with more states - code needs changing
		currentAliveNeighbors += gameGrid.GetCellValue(neighborRow, neighborCol);
	}

	return currentAliveNeighbors;
}

void SimulationManager::Update()
{
	if (IsSimRunning())
	{
		// Check every cell of the grid in current simulation
		for (int currentRow = 0; currentRow < gameGrid.GetTotalGridRows(); currentRow++)
		{
			for (int currentCol = 0; currentCol < gameGrid.GetTotalGridColumns(); currentCol++)
			{
				// Counting neighbors for every cell
				int currentAliveNeigbors = CountAliveNeighborsInSim(currentRow, currentCol);
				// Getting the cell value of each cell
				int currentCellValue = gameGrid.GetCellValue(currentRow, currentCol);

				// Implementing consolidated Rule #1 (Underpopulation and Overpopulation) for Game of Life
				// RULE #1: If a cell is alive, it dies when it has less than 2 or more than 3 alive neignbors, else it stays alive 
				if (currentCellValue == 1)
				{
					if (currentAliveNeigbors < 2 || currentAliveNeigbors > 3)
					{
						// Cell becomes dead
						tempGrid.SetCellValue(currentRow, currentCol, 0);
					}
					else
					{
						// Cell stays alive
						tempGrid.SetCellValue(currentRow, currentCol, 1);
					}
				}
				// Implementing consolidated Rule #2 (Stasis and Reproduction) for Game of Life
				// RULE #2: If a cell is dead it can come alive only if it has exactly 3 neighbors alive, else it stays dead
				else
				{
					if (currentAliveNeigbors == 3)
					{
						// Cell becomes alive
						tempGrid.SetCellValue(currentRow, currentCol, 1);
					}
					else
					{
						// Cell stays dead
						tempGrid.SetCellValue(currentRow, currentCol, 0);
					}
				}
			}
		}
		// Copying over values from the temporary grid to original grid
		// TODO: Can be made efficient here if we do multithreading or GPU driven arch.
		gameGrid = tempGrid;
	}
}

void SimulationManager::ClearSimulationGrid()
{
	if (!IsSimRunning())
	{
		gameGrid.ClearGrid();
	}
}

void SimulationManager::CreateRandomState()
{
	if (!IsSimRunning())
	{
		gameGrid.FillGridRandomly();
	}
}

void SimulationManager::ToggleCellInSimulation(int cellRowInSim, int cellColumnInSim)
{
	if (!IsSimRunning())
	{
		gameGrid.ToggleGridCell(cellRowInSim, cellColumnInSim);
	}
}
