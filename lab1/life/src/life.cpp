/**
 * created by chrna581, Christoffer Näs and miklu523, Mikael Lundgren .
 * The project relizes the Game Of Life Simulation by n J. H. Conway
 * The program reads a text file that represents the starting condition for the simulation.
 * The you can simulate the simulation step by step or through an animation.
*/

#include <iostream>
#include <fstream>
#include "grid.h"
#include "lifeutil.h"
#include <string>

using namespace std;

int checkNrOfNeighbours(const Grid<char>& grid,const int& origRow,const int& origCol);

Grid<char> genNextGeneration(const Grid<char>& grid);

void printGrid(const Grid<char> &grid);

void printWelcomeMessage();

bool choiceMenu(Grid<char>& grid);

bool animate(Grid<char>& grid);

bool tick(Grid<char>& grid);

/**
 *
 * Reads a text file that represents the starting condition for the simulation.
 * Creates a grid that represent the starting condition.
 * Contains the running loop for the simulation.
 *
 * @return 0 to close the program
 */
int main() {
    printWelcomeMessage();
    string fileName;
    cout << "Grid input file name? ";
    cin >> fileName;
    fstream mapFile;
    mapFile.open(fileName);
    int rowCount;
    int colCount;
    mapFile >> rowCount >> colCount;
    Grid<char> grid = Grid<char>(rowCount,colCount);

    for(int row = 0; row < rowCount; row++){
        for(int col = 0; col < colCount; col++){
            //grid.set(row,col, mapFile.get());
            char character = (char)mapFile.get();
            if(character == '-' || character == 'X'){
            grid.set(row, col, character);
            }
            else{
                col--;
            }
        }
    }

    printGrid(grid);
    mapFile.close();
    bool simulationRunning = true;
    while (simulationRunning) {
        simulationRunning = tick(grid);
        if(simulationRunning){
            grid = genNextGeneration(grid);
            printGrid(grid);
        }
    }
    cout << "Have a nice Life! "  << endl;
    return 0;
}

/**
 * Creates the next generation in the simulation
 *
 * @param grid The previous generation represented in a grig
 * @return The next generation in the simulation represented in a grid
 */
Grid<char> genNextGeneration(const Grid<char>& grid){
    Grid<char> newGrid = Grid<char>(grid.numRows(), grid.numCols());
    for(int row = 0; row < grid.numRows(); row++){
        for(int col = 0; col < grid.numCols(); col++){
            switch (checkNrOfNeighbours(grid, row, col)) {
                case 0:
                case 1:
                    newGrid.set(row, col, '-');
                    break;
                case 2:
                    newGrid.set(row, col, grid.get(row, col));
                    break;
                case 3:
                    newGrid.set(row, col , 'X');
                    break;
                case 4:
                    newGrid.set(row, col, '-');
                    break;
                default:
                    break;
            }
        }
    }
    return newGrid;
}

/**
 * Counts the number of neighbours containing 'X' in a grid
 *
 * @param grid Grid which the function operates on
 * @param origRow X cordinate in grid which neighbours are counted
 * @param origCol Y cordinate in grid which neighbours are counted
 * @return The number of neighbours containing 'X' in grid
 */
int checkNrOfNeighbours(const Grid<char>& grid,const int& origRow,const int& origCol){
    int nrOfNeighbours = 0;
    for(int row = (origRow-1); row < origRow+2; row++){
        for(int col = (origCol-1); col < origCol+2; col++){
            if(grid.inBounds(row, col) && (col != origCol || row != origRow)){
                if(grid.get(row, col) == 'X'){
                    nrOfNeighbours++;
                }
            }
        }
    }
    if(nrOfNeighbours > 4){
        nrOfNeighbours = 4;
    }
    return nrOfNeighbours;
}

/**
 *Prints welcome message and rules for the simulation for the user in the console
 *
*/
void printWelcomeMessage(){
    cout <<"Welcome to the TDDD86 Game of Life,"<<endl;
    cout <<"a simulation of the lifecycle of a bacteria colony."<<endl;
    cout <<"Cells (X) live and die by the following rules:"<<endl;
    cout <<"- A cell with 1 or fewer neighbours dies."<<endl;
    cout <<"- Locations with 3 neighbours will create life."<<endl;
    cout <<"- A cell with 4 or more neighbours dies."<<endl;
}

/**
 * Prints the elements of the grid in the console row for row, column by column
 *
 * @param grid Grid which elements are printed in the console
 */
void printGrid(const Grid<char> &grid){
    int rowCount = grid.numRows();
    int colCount = grid.numCols();
    for(int row = 0; row < rowCount; row++){
        cout << endl;
        for(int col = 0; col < colCount; col++){
            cout << grid.get(row,col);
        }
    }
    cout <<endl;
}

/**
 * takes a keyboard input from console and contuinues operations accordingly.
 * 'a' = animate, 't' = tick, 'q' = quit.
 *
 * @param grid The grid from the previuos tick
 * @return continues simulation if returns true, quits simulation if returns false
 */
bool tick(Grid<char>& grid){
    cout <<"a)nimate, t)ick,q)uit"<<endl;
    char choice;
    cin >> choice;
    switch (choice) {
        case 'a':
            return animate(grid);
            break;
        case 't':
            clearConsole();
            return true;
            break;
        case 'q':
            return false;
            break;
        default:
            return true;
    }
}

/**
 * @brief Initiates a permanent loop that animates the generation of new grids
 * @param grid
 * @return True to continue simulation
 */
bool animate(Grid<char>& grid){
    bool animating = true;
    while (animating) {
        pause(1000);
        clearConsole();
        grid = genNextGeneration(grid);
        printGrid(grid);
    }
    return true;
}








