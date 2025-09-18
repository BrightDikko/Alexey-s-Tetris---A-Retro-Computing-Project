#pragma once
#include <raylib.h>

#include <map>
#include <vector>

struct GridPosition {
    int row;
    int column;
    GridPosition(int r, int c) : row(r), column(c) {}
};

class Tetromino {
   public:
    Tetromino();
    void Render(int offsetX, int offsetY);
    void RenderWithCellSize(int offsetX, int offsetY, int cellSize) const;
    std::vector<GridPosition> CellsAtOrigin() const;
    void Translate(int rowChange, int columnChange);
    std::vector<GridPosition> CurrentCellPositions();
    void RotateClockwise();
    void RotateCounterClockwise();
    int GetColorIndex() const { return colorIndex; }

   protected:
    void Initialize(int index, int variationId, int rowShiftInit,
                    int colShiftInit);
    int colorIndex;
    int squareSize;
    int activeRotation;
    int rowShift;
    int columnShift;
    std::map<int, std::vector<GridPosition>> rotationPatterns;
    std::vector<Color> colorPalette;
};

class TetrominoVariation1 : public Tetromino { public: TetrominoVariation1(); };
class TetrominoVariation2 : public Tetromino { public: TetrominoVariation2(); };
class TetrominoVariation3 : public Tetromino { public: TetrominoVariation3(); };
class TetrominoVariation4 : public Tetromino { public: TetrominoVariation4(); };
class TetrominoVariation5 : public Tetromino { public: TetrominoVariation5(); };
class TetrominoVariation6 : public Tetromino { public: TetrominoVariation6(); };
class TetrominoVariation7 : public Tetromino { public: TetrominoVariation7(); };