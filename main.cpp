#include <raylib.h>
#include "./src/simulationManager.hpp"

int main(void)
{
    // Background color (RGBA)
    Color BG_GREY = { 29,29,29,255 };
    // Create simulation window - (0,0) is top left
    const int WINDOW_WIDTH = 750;
    const int WINDOW_HEIGHT = 750;
    // Size of each individual cell in the grid (equal sized square)
    const int CELL_SIZE = 25;
    int FPS = 12;

    // Initialize with the title of the window
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game of Life");

    // Define how fast the simulation should run - defines the ceiling and 
    // will not run more than 12 times a second (might run slower)
    // Means code inside while loop runs 12 times every second
    SetTargetFPS(FPS);

    // Creating a Simulation Manager Object
    SimulationManager currentSimulation{ WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE };

    // Simulation loop (3 parts) - Event Handling, Updating State, Drawing Objects
    while (WindowShouldClose() == false)
    {
        // Event Handling
        // Adding mouse click interactivity to make grids
        // TODO: NOT WORKING ATM; Grid clears after making pattern and then pressing Enter
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            // Capturing the mouse's (X,Y) position on screen
            Vector2 mousePosition = GetMousePosition();
            // Calculating over which cell the mouse is located
            int mouseOverRow = mousePosition.y / CELL_SIZE;
            int mouseOverColumn = mousePosition.x / CELL_SIZE;
            // Calling the actual toggle function via the simulation
            currentSimulation.ToggleCellInSimulation(mouseOverRow, mouseOverColumn);
        }

        // When user presses ENTER key, start sim & SPACE key stops it
        if (IsKeyPressed(KEY_ENTER))
        {
            currentSimulation.StartSimulation();
            SetWindowTitle("Running Game of Life...");
        }
        else if (IsKeyPressed(KEY_SPACE))
        {
            currentSimulation.StopSimulation();
            SetWindowTitle("Paused Game of Life...");
        }
        // Changing FPS by pressing the UP or DOWN arrow key
        else if (IsKeyPressed(KEY_UP))
        {
            FPS += 2;
            SetTargetFPS(FPS);
        }
        else if (IsKeyPressed(KEY_DOWN))
        {
            if (FPS > 5)
            {
                FPS -= 2;
                SetTargetFPS(FPS);
            }
        }
        // Setting a random starting grid when grid is clear
        else if (IsKeyPressed(KEY_R))
        {
            currentSimulation.CreateRandomState();
        }
        // Clearing the grid when paused
        else if (IsKeyPressed(KEY_C))
        {
            currentSimulation.ClearSimulationGrid();
        }

        // Updating State
        currentSimulation.Update();

        // Drawing Grid
        BeginDrawing(); // Create a blank objects to draw game objects on
        ClearBackground(BG_GREY); // Done after each frame of simulation loop - wipes previous frame artifacts
        //"Drawing" the current simulation
        currentSimulation.DrawGridInSim();
        EndDrawing(); // Ends the canvas drawing
    }

    CloseWindow();

    return 0;
}