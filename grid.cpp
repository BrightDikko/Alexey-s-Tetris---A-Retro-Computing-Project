#include <iostream>

#include "grid.h"

Grid::Grid() {
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    Initialize();
    colors = GetCellColors();
}

void Grid::Initialize() {
    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numCols; column++) {
            grid[row][column] = 0;
        }
    }
}

void Grid::Print() {
    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numCols; column++) {
            std::cout << grid[row][column] << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<Color> Grid::GetCellColors() {
    Color darkGrey = {26, 31, 40, 255};
    Color green = {47, 230, 23, 255};
    Color red = {255, 0, 0, 255};
    Color orange = {255, 165, 0, 255};
    Color yellow = {255, 255, 0, 255};
    Color purple = {200, 122, 255, 255};
    Color cyan = {0, 255, 255, 255};
    Color blue = {0, 0, 255, 255};

    return {darkGrey, green, red, orange, yellow, purple, cyan, blue};
}

void Grid::DrawAt(int offsetX, int offsetY) {
    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numCols; column++) {
            int cellValue = grid[row][column];
            DrawRectangle(offsetX + column * cellSize + 1,
                          offsetY + row * cellSize + 1, cellSize - 1,
                          cellSize - 1, colors[cellValue]);
        }
    }

    Color gridLine = {255, 255, 255, 20};
    int width = numCols * cellSize;
    int height = numRows * cellSize;

    for (int c = 0; c <= numCols; ++c) {
        DrawLine(offsetX + c * cellSize, offsetY, offsetX + c * cellSize,
                 offsetY + height, gridLine);
    }
    for (int r = 0; r <= numRows; ++r) {
        DrawLine(offsetX, offsetY + r * cellSize, offsetX + width,
                 offsetY + r * cellSize, gridLine);
    }
}

bool Grid::IsCellOutside(int row, int col) const {
    return (row < 0 || row >= numRows || col < 0 || col >= numCols);
}

bool Grid::IsCellEmpty(int row, int col) const {
    if (!IsCellOutside(row, col)) {
        return grid[row][col] == 0;
    }
    return false;
}

int Grid::SweepAndClearFullRows() {
    int clearedCount = 0;

    for (int row = numRows - 1; row >= 0; row--) {
        if (RowIsCompletelyFilled(row)) {
            ClearSingleRow(row);
            clearedCount++;
        } else if (clearedCount > 0) {
            DropRowByOffset(row, clearedCount);
        }
    }

    return clearedCount;
}

bool Grid::RowIsCompletelyFilled(int row) const {
    for (int col = 0; col < numCols; col++) {
        if (grid[row][col] == 0) {
            return false;
        }
    }
    return true;
}

void Grid::ClearSingleRow(int row) {
    for (int col = 0; col < numCols; col++) {
        grid[row][col] = 0;
    }
}

void Grid::DropRowByOffset(int row, int offset) {
    for (int col = 0; col < numCols; col++) {
        grid[row + offset][col] = grid[row][col];
        grid[row][col] = 0;
    }
}
