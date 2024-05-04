#include <stdio.h>
extern "C"
{
#include <raylib.h>
#include <rlgl.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
}

float sx = 0;
float sy = 0;

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
    float rotation;
    const char *label;

    void draw()
    {
        rlPushMatrix();
        rlTranslatef(x, y, 0.0f);
        rlRotatef(rotation, 0, 0, 1);
        rlTranslatef(-x, -y, 0.0f);

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
        rlPopMatrix();
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
    MX_MAR.rotation = 0;

    InitWindow(800, 600, "Little Cpu");

    SetTargetFPS(30);
    bool rotate = 0;
    while (!WindowShouldClose())
    {
        // if (rotate)
        BeginDrawing();
        ClearBackground(BLACK);

        if (GuiCheckBox((Rectangle){100, 0, 60, 18}, "Spin!", &rotate))
            MX_MAR.rotation = 0;

        GuiSlider((Rectangle){100, 20, 60, 18}, "-", "+ x", &sx, 0, 100);
        GuiSlider((Rectangle){100, 20 + 18, 60, 18}, "-", "+ y", &sy, 0, 100);
        MX_MAR.rotation = sx;

        PC.draw();
        MAR.draw();
        MDR.draw();
        MX_MAR.draw();

        DrawFPS(0, 0);
        EndDrawing();
    }

    CloseWindow();
}