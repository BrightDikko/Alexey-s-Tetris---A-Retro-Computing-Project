#include <algorithm>
#include <cmath>
#include <random>

#include "game.h"

Game::Game()
    : gameOver(false),
      grid(),
      currentTetromino(CreateRandomTetromino()),
      nextTetromino(CreateRandomTetromino()),
      playfieldX(120),
      playfieldY(20),
      cellSize(30),
      sidebarWidth(300),
      sidebarGap(24),
      totalLines(0),
      level(1),
      score(0),
      highScore(0),
      startTimeSeconds(GetTime()),
      gameDurationSeconds(0.0) {}

void Game::RenderGame() {
    ReflowLayout();
    DrawPlayfieldBezel();
    grid.DrawAt(playfieldX, playfieldY);
    currentTetromino.Render(playfieldX, playfieldY);
    DrawSidePanels();

    if (gameOver) {
        Color overlayColor = {0, 0, 0, 160};
        int playfieldWidth = 10 * cellSize;
        int playfieldHeight = 20 * cellSize;
        DrawRectangle(playfieldX, playfieldY, playfieldWidth, playfieldHeight, overlayColor);

        const int gameOverFontSize = 30;
        const char* gameOverText = "GAME OVER";
        int gameOverTextWidth = MeasureText(gameOverText, gameOverFontSize);
        DrawText(gameOverText, playfieldX + (playfieldWidth - gameOverTextWidth) / 2, playfieldY + playfieldHeight / 2 - 130, gameOverFontSize, WHITE);

        int statsLeftX = playfieldX + 24;
        int statsTopY = playfieldY + playfieldHeight / 2 - 80;
        Color labelColor = Fade(WHITE, 0.85f);

        int elapsedMinutes = static_cast<int>(gameDurationSeconds / 60.0);
        int elapsedSeconds = static_cast<int>(gameDurationSeconds) % 60;

        const int labelFontSize = 20;
        const int lineHeight = 28;

        int labelColumnX = statsLeftX;
        int valueColumnX = statsLeftX + 160;

        DrawText("LINES", labelColumnX, statsTopY, labelFontSize, labelColor);
        DrawText(TextFormat("%d", totalLines), valueColumnX, statsTopY, labelFontSize, labelColor);
        statsTopY += lineHeight;

        DrawText("LEVEL", labelColumnX, statsTopY, labelFontSize, labelColor);
        DrawText(TextFormat("%d", level), valueColumnX, statsTopY, labelFontSize, labelColor);
        statsTopY += lineHeight;

        DrawText("SCORE", labelColumnX, statsTopY, labelFontSize, labelColor);
        DrawText(TextFormat("%d", score), valueColumnX, statsTopY, labelFontSize, labelColor);
        statsTopY += lineHeight;

        DrawText("TIME", labelColumnX, statsTopY, labelFontSize, labelColor);
        DrawText(TextFormat("%02d:%02d", elapsedMinutes, elapsedSeconds), valueColumnX, statsTopY, labelFontSize, labelColor);
        statsTopY += lineHeight;

        DrawText("HIGH", labelColumnX, statsTopY, labelFontSize, labelColor);
        DrawText(TextFormat("%d", highScore), valueColumnX, statsTopY, labelFontSize, labelColor);
        statsTopY += 40;

        const char* restartHintText = "Press any key to restart";
        int restartHintTextWidth = MeasureText(restartHintText, 18);
        DrawText(restartHintText, playfieldX + (playfieldWidth - restartHintTextWidth) / 2, statsTopY, 18, WHITE);
    }
}

void Game::ReflowLayout() {
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    const int playfieldWidth = 10 * cellSize;
    const int playfieldHeight = 20 * cellSize;
    const int requiredWidth = playfieldWidth + sidebarGap + sidebarWidth;
    const int minMarginX = 16;
    const int minMarginY = 16;

    int marginX = (screenWidth - requiredWidth) / 2;
    if (marginX < minMarginX) marginX = minMarginX;

    int marginY = (screenHeight - playfieldHeight) / 2;
    if (marginY < minMarginY) marginY = minMarginY;

    playfieldX = marginX;
    playfieldY = marginY;
}

void Game::DrawPlayfieldBezel() const {
    int playfieldWidth = 10 * cellSize;
    int playfieldHeight = 20 * cellSize;
    Color outerShadowColor = {0, 0, 0, 60};
    DrawRectangle(playfieldX - 6, playfieldY - 6, playfieldWidth + 12, playfieldHeight + 12, outerShadowColor);
    Color frameColor = {0, 220, 255, 255};
    DrawRectangleLinesEx({(float)playfieldX - 4, (float)playfieldY - 4, (float)playfieldWidth + 8, (float)playfieldHeight + 8}, 4, frameColor);
    Color boardBackgroundColor = {20, 28, 38, 255};
    DrawRectangle(playfieldX, playfieldY, playfieldWidth, playfieldHeight, boardBackgroundColor);
}

void Game::DrawSidePanels() {
    int sidebarOriginX = playfieldX + (10 * cellSize) + sidebarGap;

    const int statsPanelHeight = 200;
    const int nextPanelHeight = 170;
    const int controlsPanelHeight = 150;
    const int panelVerticalGap = 16;

    int currentPanelTopY = playfieldY;
    DrawStatsPanel(sidebarOriginX, currentPanelTopY, statsPanelHeight);
    currentPanelTopY += statsPanelHeight + panelVerticalGap;

    DrawNextPanel(sidebarOriginX, currentPanelTopY, nextPanelHeight);
    currentPanelTopY += nextPanelHeight + panelVerticalGap;

    DrawControlsPanel(sidebarOriginX, currentPanelTopY, controlsPanelHeight);
}

void Game::DrawStatsPanel(int anchorX, int anchorY, int panelHeight) {
    Color panelBackgroundColor = {10, 16, 26, 200};
    DrawRectangleRounded({(float)anchorX, (float)anchorY, (float)sidebarWidth, (float)panelHeight}, 0.12f, 8, panelBackgroundColor);
    DrawRectangleRoundedLines({(float)anchorX, (float)anchorY, (float)sidebarWidth, (float)panelHeight}, 0.12f, 8, Fade(WHITE, 0.2f));

    int labelColumnX = anchorX + 14;
    int currentRowY = anchorY + 14;
    DrawText("STATS", labelColumnX, currentRowY, 18, Fade(WHITE, 0.85f));

    double elapsedTimeSeconds = gameOver ? gameDurationSeconds : (GetTime() - startTimeSeconds);
    int elapsedMinutes = static_cast<int>(elapsedTimeSeconds / 60.0);
    int elapsedSeconds = static_cast<int>(elapsedTimeSeconds) % 60;

    const int statsFontSize = 20;
    const int rowVerticalSpacing = 28;
    const int valueColumnX = anchorX + sidebarWidth - 150;

    currentRowY += 36;
    DrawText("LINES", labelColumnX, currentRowY, statsFontSize, WHITE);
    DrawText(TextFormat("%d", totalLines), valueColumnX, currentRowY, statsFontSize, WHITE);
    currentRowY += rowVerticalSpacing;

    DrawText("LEVEL", labelColumnX, currentRowY, statsFontSize, WHITE);
    DrawText(TextFormat("%d", level), valueColumnX, currentRowY, statsFontSize, WHITE);
    currentRowY += rowVerticalSpacing;

    DrawText("SCORE", labelColumnX, currentRowY, statsFontSize, WHITE);
    DrawText(TextFormat("%d", score), valueColumnX, currentRowY, statsFontSize, WHITE);
    currentRowY += rowVerticalSpacing;

    DrawText("TIME", labelColumnX, currentRowY, statsFontSize, WHITE);
    DrawText(TextFormat("%02d:%02d", elapsedMinutes, elapsedSeconds), valueColumnX, currentRowY, statsFontSize, WHITE);
    currentRowY += rowVerticalSpacing;

    DrawText("HIGH", labelColumnX, currentRowY, statsFontSize, WHITE);
    DrawText(TextFormat("%d", highScore), valueColumnX, currentRowY, statsFontSize, WHITE);
}

void Game::DrawNextPanel(int anchorX, int anchorY, int panelH) {
    int panelHeight = panelH;
    Color panelBackgroundColor = {10, 16, 26, 200};
    DrawRectangleRounded({(float)anchorX, (float)anchorY, (float)sidebarWidth, (float)panelHeight}, 0.12f, 8, panelBackgroundColor);
    DrawRectangleRoundedLines({(float)anchorX, (float)anchorY, (float)sidebarWidth, (float)panelHeight}, 0.12f, 8, Fade(WHITE, 0.2f));

    int titleX = anchorX + 14;
    DrawText("NEXT", titleX, anchorY + 14, 18, Fade(WHITE, 0.85f));

    const int previewCellSize = 18;
    const int innerPaddingTop = 56;
    const int innerPaddingSide = 14;

    int innerContentWidth = sidebarWidth - innerPaddingSide * 2;
    int innerContentHeight = panelHeight - innerPaddingTop - innerPaddingSide;

    int previewWidth = 4 * previewCellSize;
    int previewHeight = 4 * previewCellSize;

    int previewOriginX = anchorX + innerPaddingSide + (innerContentWidth - previewWidth) / 2;
    int previewOriginY = anchorY + innerPaddingTop + (innerContentHeight - previewHeight) / 2;

    DrawRectangle(previewOriginX - 4, previewOriginY - 4, previewWidth + 8, previewHeight + 8, Fade(BLACK, 0.25f));
    nextTetromino.RenderWithCellSize(previewOriginX, previewOriginY, previewCellSize);
}

void Game::DrawControlsPanel(int anchorX, int anchorY, int panelHeight) {
    Color panelBackgroundColor = {10, 16, 26, 200};
    DrawRectangleRounded({(float)anchorX, (float)anchorY, (float)sidebarWidth, (float)panelHeight}, 0.12f, 8, panelBackgroundColor);
    DrawRectangleRoundedLines({(float)anchorX, (float)anchorY, (float)sidebarWidth, (float)panelHeight}, 0.12f, 8, Fade(WHITE, 0.2f));

    int titleX = anchorX + 14;
    int currentTextY = anchorY + 14;
    DrawText("CONTROLS", titleX, currentTextY, 18, Fade(WHITE, 0.85f));
    currentTextY += 36;

    const int keyFontSize = 15;
    const int descriptionFontSize = 15;
    const int lineSpacing = 22;

    int keyColumnX = titleX;
    int descriptionColumnX = titleX + 120;

    DrawText("Left / Right", keyColumnX, currentTextY, keyFontSize, WHITE);
    DrawText("Move piece", descriptionColumnX, currentTextY, descriptionFontSize, Fade(WHITE, 0.9f));
    currentTextY += lineSpacing;

    DrawText("Up", keyColumnX, currentTextY, keyFontSize, WHITE);
    DrawText("Rotate", descriptionColumnX, currentTextY, descriptionFontSize, Fade(WHITE, 0.9f));
    currentTextY += lineSpacing;

    DrawText("Down", keyColumnX, currentTextY, keyFontSize, WHITE);
    DrawText("Soft drop (+1/row)", descriptionColumnX, currentTextY, descriptionFontSize, Fade(WHITE, 0.9f));
    currentTextY += lineSpacing;

    DrawText("Space", keyColumnX, currentTextY, keyFontSize, WHITE);
    DrawText("Hard drop (+2/row)", descriptionColumnX, currentTextY, descriptionFontSize, Fade(WHITE, 0.9f));
}

void Game::HandlePlayerInput() {
    int pressedKeyCode = GetKeyPressed();

    if (gameOver) {
        if (pressedKeyCode != 0) {
            gameOver = false;
            ResetState();
        }
        return;
    }

    if (IsKeyPressed(KEY_LEFT)) MoveLeft();
    if (IsKeyPressed(KEY_RIGHT)) MoveRight();
    if (IsKeyPressed(KEY_DOWN)) SoftDropOneRow();
    if (IsKeyPressed(KEY_UP)) RotateActiveTetromino();
    if (IsKeyPressed(KEY_SPACE)) HardDrop();
}

void Game::SoftDropOneRow() {
    if (gameOver) return;

    currentTetromino.Translate(+1, 0);
    if (IsCurrentTetrominoOutOfBounds() || !CurrentTetrominoFitsGrid()) {
        currentTetromino.Translate(-1, 0);
        LockCurrentTetromino();
    } else {
        score += 1;
    }
}

void Game::HardDrop() {
    if (gameOver) return;

    int droppedRowCount = 0;
    for (;;) {
        currentTetromino.Translate(+1, 0);
        if (IsCurrentTetrominoOutOfBounds() || !CurrentTetrominoFitsGrid()) {
            currentTetromino.Translate(-1, 0);
            break;
        }
        droppedRowCount++;
    }
    if (droppedRowCount > 0) score += 2 * droppedRowCount;
    LockCurrentTetromino();
}

void Game::StepGravity() {
    if (gameOver) return;

    currentTetromino.Translate(+1, 0);
    if (IsCurrentTetrominoOutOfBounds() || !CurrentTetrominoFitsGrid()) {
        currentTetromino.Translate(-1, 0);
        LockCurrentTetromino();
    }
}

double Game::GetFallIntervalSeconds() const {
    const double baseIntervalSeconds = 0.40;
    const double speedupFactorPerLevel = 0.90;
    const double minimumIntervalSeconds = 0.05;
    double computedIntervalSeconds =
        baseIntervalSeconds *
        std::pow(speedupFactorPerLevel, std::max(0, level - 1));
    return (computedIntervalSeconds < minimumIntervalSeconds) ? minimumIntervalSeconds : computedIntervalSeconds;
}

void Game::MoveLeft() {
    if (gameOver) return;
    AttemptTranslationOrRevert(0, -1);
}

void Game::MoveRight() {
    if (gameOver) return;
    AttemptTranslationOrRevert(0, +1);
}

void Game::AttemptTranslationOrRevert(int rowChange, int columnChange) {
    currentTetromino.Translate(rowChange, columnChange);
    if (IsCurrentTetrominoOutOfBounds() || !CurrentTetrominoFitsGrid()) {
        currentTetromino.Translate(-rowChange, -columnChange);
    }
}

void Game::RotateActiveTetromino() {
    if (gameOver) return;
    currentTetromino.RotateClockwise();
    if (IsCurrentTetrominoOutOfBounds() || !CurrentTetrominoFitsGrid()) {
        currentTetromino.RotateCounterClockwise();
    }
}

bool Game::IsCurrentTetrominoOutOfBounds() const {
    auto& tetrominoRef = const_cast<Tetromino&>(currentTetromino);
    auto& gridRef = const_cast<Grid&>(grid);
    std::vector<GridPosition> tetrominoCells = tetrominoRef.CurrentCellPositions();
    for (const auto& cellPosition : tetrominoCells) {
        if (gridRef.IsCellOutside(cellPosition.row, cellPosition.column))
            return true;
    }
    return false;
}

bool Game::CurrentTetrominoFitsGrid() const {
    auto& tetrominoRef = const_cast<Tetromino&>(currentTetromino);
    auto& gridRef = const_cast<Grid&>(grid);
    std::vector<GridPosition> tetrominoCells = tetrominoRef.CurrentCellPositions();
    for (const auto& cellPosition : tetrominoCells) {
        if (!gridRef.IsCellEmpty(cellPosition.row, cellPosition.column))
            return false;
    }
    return true;
}

void Game::LockCurrentTetromino() {
    std::vector<GridPosition> tetrominoCells = currentTetromino.CurrentCellPositions();
    const int tetrominoColor = currentTetromino.GetColorIndex();

    for (const auto& cellPosition : tetrominoCells) {
        grid.grid[cellPosition.row][cellPosition.column] = tetrominoColor;
    }

    int clearedRowCount = grid.SweepAndClearFullRows();

    if (clearedRowCount > 0) {
        int baseScoreAward = 0;

        if (clearedRowCount == 1) {
            baseScoreAward = 100;
        } else if (clearedRowCount == 2) {
            baseScoreAward = 300;
        } else if (clearedRowCount == 3) {
            baseScoreAward = 500;
        } else {
            baseScoreAward = 800;
        }

        score += baseScoreAward * level;
        totalLines += clearedRowCount;
        level = 1 + (totalLines / 2);
    }

    currentTetromino = nextTetromino;
    nextTetromino = CreateRandomTetromino();

    if (!CurrentTetrominoFitsGrid()) {
        gameOver = true;
        gameDurationSeconds = GetTime() - startTimeSeconds;

        if (score > highScore) {
            highScore = score;
        }
    }
}

Tetromino Game::CreateRandomTetromino() {
    static std::mt19937 randomGenerator(std::random_device{}());
    std::uniform_int_distribution<int> tetrominoTypeDistribution(1, 7);
    const int randomPickValue = tetrominoTypeDistribution(randomGenerator);
    switch (randomPickValue) {
        case 1:
            return TetrominoVariation1();
        case 2:
            return TetrominoVariation2();
        case 3:
            return TetrominoVariation3();
        case 4:
            return TetrominoVariation4();
        case 5:
            return TetrominoVariation5();
        case 6:
            return TetrominoVariation6();
        default:
            return TetrominoVariation7();
    }
}

void Game::ResetState() {
    grid.Initialize();
    currentTetromino = CreateRandomTetromino();
    nextTetromino = CreateRandomTetromino();
    totalLines = 0;
    level = 1;
    score = 0;
    startTimeSeconds = GetTime();
    gameDurationSeconds = 0.0;
}