#pragma once
#include "grid.hpp"

class SimulationManager
{
private: 
	Grid gameGrid;
	Grid tempGrid;
	bool simRunning { false };

public:

	// Initializer list by providing a function
	SimulationManager(int currentGridWidth, int currentWidthHeight, int currentCellSize) :
		gameGrid(currentGridWidth, currentWidthHeight, currentCellSize),
		tempGrid(currentGridWidth, currentWidthHeight, currentCellSize), 
		simRunning(false)
		{
			//// If you keep this piece of code then the grid will get filled in manually
			//gameGrid.FillGridRandomly();
		};

	void DrawGridInSim();
	void SetCellValueInSim(int cellRowInSim, int cellColumnInSim, int valueInSim);
	int CountAliveNeighborsInSim(int cellRowInSim, int cellColumnInSim);
	void Update();
	bool IsSimRunning() { return simRunning; }
	void StartSimulation() { simRunning = true; }
	void StopSimulation() { simRunning = false; }
	void ClearSimulationGrid();
	void CreateRandomState();
	void ToggleCellInSimulation(int cellRowInSim, int cellColumnInSim);
};