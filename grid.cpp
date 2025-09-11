#include "grid.h"
#include <iostream>

Grid::Grid()
{
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    Initalize();
    colors = GetCellColors();  
}

void Grid::Initalize()
{
    for(int row=0; row < numRows; row++){
        for(int column = 0; column <numCols; column++){
            grid[row][column] = 0;
        }
    }
}

void Grid::Print()
{
    for(int row = 0; row < numRows; row++){
        for(int column =0; column < numCols; column++){
            std::cout << grid[row][column] << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<Color> Grid::GetCellColors()
{
    Color darkGrey = {26, 31, 40, 255};
    Color green = {47, 230, 23, 255};
    Color red = {255, 0, 0, 255};
    Color orange = {255, 165, 0, 255};
    Color yellow = {255, 255, 0, 255};
    Color purple = {200, 122, 255, 255};
    Color cyan = {0, 255, 255, 255};
    Color blue = {0, 0, 255, 255};

    return {darkGrey, green, red, orange, yellow, purple, cyan};


}

void Grid::Draw()
{
    for (int row=0; row < numRows; row++){
        for (int column=0; column < numCols; column++){
            int cellValue = grid[row][column];
            DrawRectangle(column*cellSize+1, row * cellSize+1, cellSize-1, cellSize-1, colors[cellValue]);

        }
    }
}