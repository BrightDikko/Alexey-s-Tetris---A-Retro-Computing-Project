#include "tetrominoes.h"

static const std::map<int, std::vector<std::vector<GridPosition>>> TetrominoRotations = {
    {1, {
        { {1,0}, {1,1}, {1,2}, {1,3} },
        { {0,2}, {1,2}, {2,2}, {3,2} },
        { {2,0}, {2,1}, {2,2}, {2,3} },
        { {0,1}, {1,1}, {2,1}, {3,1} }
    }},
    {2, {
        { {0,0}, {1,0}, {1,1}, {1,2} },
        { {0,1}, {0,2}, {1,1}, {2,1} },
        { {1,0}, {1,1}, {1,2}, {2,2} },
        { {0,1}, {1,1}, {2,0}, {2,1} }
    }},
    {3, {
        { {0,2}, {1,0}, {1,1}, {1,2} },
        { {0,1}, {1,1}, {2,1}, {2,2} },
        { {1,0}, {1,1}, {1,2}, {2,0} },
        { {0,0}, {0,1}, {1,1}, {2,1} }
    }},
    {4, {
        { {0,0}, {0,1}, {1,0}, {1,1} }
    }},
    {5, {
        { {0,1}, {0,2}, {1,0}, {1,1} },
        { {0,1}, {1,1}, {1,2}, {2,2} },
        { {1,1}, {1,2}, {2,0}, {2,1} },
        { {0,0}, {1,0}, {1,1}, {2,1} }
    }},
    {6, {
        { {0,1}, {1,0}, {1,1}, {1,2} },
        { {0,1}, {1,1}, {1,2}, {2,1} },
        { {1,0}, {1,1}, {1,2}, {2,1} },
        { {0,1}, {1,0}, {1,1}, {2,1} }
    }},
    {7, {
        { {0,0}, {0,1}, {1,1}, {1,2} },
        { {0,2}, {1,1}, {1,2}, {2,1} },
        { {1,0}, {1,1}, {2,1}, {2,2} },
        { {0,1}, {1,0}, {1,1}, {2,0} }
    }}
};

Tetromino::Tetromino() {
    squareSize = 30;
    activeRotation = 0;
    rowShift = 0;
    columnShift = 0;
    colorPalette = {
        Color{26, 31, 40, 255},
        Color{47, 230, 23, 255},
        Color{232, 18, 18, 255},
        Color{226, 116, 17, 255},
        Color{237, 234, 4, 255},
        Color{166, 0, 247, 255},
        Color{21, 204, 209, 255},
        Color{13, 64, 216, 255}
    };
}

void Tetromino::Initialize(int index, int variationId, int rowShiftInit, int colShiftInit) {
    colorIndex = index;
    rotationPatterns.clear();
    const auto& rotations = TetrominoRotations.at(variationId);
    for (size_t i = 0; i < rotations.size(); ++i) {
        rotationPatterns[static_cast<int>(i)] = rotations[i];
    }
    Translate(rowShiftInit, colShiftInit);
}

void Tetromino::Render(int offsetX, int offsetY) {
    auto cells = CurrentCellPositions();
    for (auto& cell : cells) {
        DrawRectangle(
            cell.column * squareSize + offsetX,
            cell.row * squareSize + offsetY,
            squareSize - 1,
            squareSize - 1,
            colorPalette[colorIndex]
        );
    }
}

void Tetromino::RenderWithCellSize(int offsetX, int offsetY, int size) const {
    auto base = rotationPatterns.at(activeRotation);
    for (const auto& cell : base) {
        DrawRectangle(
            offsetX + cell.column * size,
            offsetY + cell.row * size,
            size - 1, size - 1,
            colorPalette[colorIndex]
        );
    }
}

void Tetromino::Translate(int rowChange, int columnChange) {
    rowShift += rowChange;
    columnShift += columnChange;
}

std::vector<GridPosition> Tetromino::CurrentCellPositions() {
    auto basePattern = rotationPatterns[activeRotation];
    std::vector<GridPosition> shiftedPattern;
    shiftedPattern.reserve(basePattern.size());
    for (auto& cell : basePattern) {
        shiftedPattern.emplace_back(cell.row + rowShift, cell.column + columnShift);
    }
    return shiftedPattern;
}

std::vector<GridPosition> Tetromino::CellsAtOrigin() const {
    return rotationPatterns.at(activeRotation);
}

void Tetromino::RotateClockwise() {
    activeRotation = (activeRotation + 1) % rotationPatterns.size();
}

void Tetromino::RotateCounterClockwise() {
    activeRotation--;
    if (activeRotation < 0) {
        activeRotation = rotationPatterns.size() - 1;
    }
}

TetrominoVariation1::TetrominoVariation1() { Initialize(1, 1, -1, 3); }
TetrominoVariation2::TetrominoVariation2() { Initialize(2, 2, 0, 3); }
TetrominoVariation3::TetrominoVariation3() { Initialize(3, 3, 0, 3); }
TetrominoVariation4::TetrominoVariation4() { Initialize(4, 4, 0, 4); }
TetrominoVariation5::TetrominoVariation5() { Initialize(5, 5, 0, 3); }
TetrominoVariation6::TetrominoVariation6() { Initialize(6, 6, 0, 3); }
TetrominoVariation7::TetrominoVariation7() { Initialize(7, 7, 0, 3); }