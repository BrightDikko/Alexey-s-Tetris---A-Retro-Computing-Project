#include <raylib.h>
#include "game.h"

int main() {
    Color darkBlue = {44, 44, 127, 255};
    InitWindow(700, 640, "Alexey's Tetris");
    SetTargetFPS(60);

    Game game;
    static double lastUpdateTime = 0.0;

    while (!WindowShouldClose()) {
        game.HandlePlayerInput();

        double now = GetTime();
        if (now - lastUpdateTime >= game.GetFallIntervalSeconds()) {
            lastUpdateTime = now;
            game.StepGravity();
        }

        BeginDrawing();
        ClearBackground(darkBlue);
        game.RenderGame();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}