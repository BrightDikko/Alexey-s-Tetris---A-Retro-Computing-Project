#pragma once
#include <raylib.h>

#include <vector>

class Grid {
   public:
    Grid();

    void Initialize();
    void Print();

    void Draw();
    void DrawAt(int offsetX, int offsetY);

    bool IsCellOutside(int row, int col) const;
    bool IsCellEmpty(int row, int col) const;

    int SweepAndClearFullRows();

    int grid[20][10];

   private:
    std::vector<Color> GetCellColors();

    bool RowIsCompletelyFilled(int row) const;
    void ClearSingleRow(int row);
    void DropRowByOffset(int row, int offset);

    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;
};