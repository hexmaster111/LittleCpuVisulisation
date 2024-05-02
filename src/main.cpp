#include <stdio.h>
#include <raylib.h>

/// @brief i_data[], o_data[], i_ld
struct REG
{
    const int w = 100;
    const int h = 32;
    const int fontsize = 18;

    float x, y;
    const char *label;
    void draw()
    {
        DrawRectangle(x, y, w, h, WHITE);
        DrawText(label, x + (w / 2) - (MeasureText(label, fontsize) / 2), y, fontsize, BLACK);
    }
} PC, MAR, MDR;

struct MUX
{
    const int triw = 25 / 2;
    const int rectw = 100;
    const int h = 32;
    const int fontsize = 18;

    float x, y;
    const char *label;

    void draw()
    {

        DrawRectangle(x, y, rectw, h, WHITE);
        DrawText(label,
                 (x + rectw / 2) - (MeasureText(label, fontsize) / 2), y,
                 fontsize, BLACK);

        DrawTriangle(
            {x + triw, y},
            {x, y},
            {x, y + h},
            BLACK);

        DrawTriangle(
            {(x + rectw) - triw, y},
            {x + rectw, y + h},
            {x + rectw, y},
            BLACK);
    }
} MX_MAR;

struct WIRE
{
};

int main(int argc, char **argv)
{
    PC.label = "PC";
    PC.x = 50;
    PC.y = 50;

    MAR.label = "MAR";
    MAR.x = 50;
    MAR.y = 100;

    MDR.label = "MDR";
    MDR.x = 50;
    MDR.y = 150;

    MX_MAR.label = "MAR";
    MX_MAR.x = 50;
    MX_MAR.y = 200;

    InitWindow(600, 400, "Little Cpu");

    SetTargetFPS(30);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        PC.draw();
        MAR.draw();
        MDR.draw();
        MX_MAR.draw();

        DrawFPS(0, 0);
        EndDrawing();
    }

    CloseWindow();
}