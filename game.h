#pragma once
#include <raylib.h>
#include <cstdlib>
#include "grid.h"
#include "tetrominoes.h"

class Game {
   public:
    Game();
    void RenderGame();
    void HandlePlayerInput();
    void SoftDropOneRow();
    void StepGravity();
    double GetFallIntervalSeconds() const;
    bool gameOver;

   private:
    void MoveLeft();
    void MoveRight();
    void AttemptTranslationOrRevert(int rowChange, int columnChange);
    void RotateActiveTetromino();
    void LockCurrentTetromino();
    void HardDrop();

    bool IsCurrentTetrominoOutOfBounds() const;
    bool CurrentTetrominoFitsGrid() const;

    Tetromino CreateRandomTetromino();
    void ResetState();

    void DrawPlayfieldBezel() const;

    void DrawSidePanels();
    void DrawStatsPanel(int anchorX, int anchorY, int panelH);
    void DrawNextPanel(int anchorX, int anchorY, int panelH);
    void DrawControlsPanel(int anchorX, int anchorY, int panelH);

    void ReflowLayout();

    Grid grid;
    Tetromino currentTetromino;
    Tetromino nextTetromino;

    int playfieldX;
    int playfieldY;
    int cellSize;
    int sidebarWidth;
    int sidebarGap;

    int totalLines;
    int level;
    int score;
    int highScore;

    double startTimeSeconds;
    double gameDurationSeconds;
};