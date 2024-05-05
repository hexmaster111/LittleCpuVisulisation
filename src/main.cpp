#include <stdio.h>
#include <assert.h>
extern "C"
{
#include <raylib.h>
#include <rlgl.h>
#define RL_VECTOR4_TYPE
#include <raymath.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
}

/// @brief i_data[], o_data[], i_ld
struct REG
{
    const float w = 100;
    const float h = 32;
    const int fontsize = 18;

    const char *label;
    Rectangle pos = {0, 0, w, h};

    void draw()
    {
        DrawRectangle(pos.x, pos.y, w, h, WHITE);
        DrawText(label, pos.x + (w / 2) - (MeasureText(label, fontsize) / 2), pos.y + 8, fontsize, BLACK);
    }
} PC, MAR, MDR;

struct MUX
{
    const float triw = 25 / 2;
    const float rectw = 100;
    const int h = 32;
    const int fontsize = 18;

    Rectangle pos = {0, 0, rectw + triw * 2, static_cast<float>(h)};

    const char *label;

    void draw()
    {
        DrawRectangle(pos.x, pos.y, rectw, h, WHITE);
        DrawText(label,
                 (pos.x + rectw / 2) - (MeasureText(label, fontsize) / 2), pos.y,
                 fontsize, BLACK);

        DrawTriangle(
            {pos.x + triw, pos.y},
            {pos.x, pos.y},
            {pos.x, pos.y + pos.height},
            BLACK);

        DrawTriangle(
            {(pos.x + rectw) - triw, pos.y},
            {pos.x + rectw, pos.y + pos.height},
            {pos.x + rectw, pos.y},
            BLACK);
    }
} MX_MAR, MX_PC, MX_ACC;

struct WIRE
{
};

struct BLOCK
{
    Rectangle *rect;
};

const int dragables_len = 6;
BLOCK dragables[dragables_len] = {
    {&MX_MAR.pos},
    {&MX_PC.pos},
    {&MX_ACC.pos},
    {&PC.pos},
    {&MAR.pos},
    {&MDR.pos},

};

struct CLICK_DRAG_HANDLER
{
private:
    BLOCK curr_item = {};
    Vector2 pos_in_item = {};

    inline Vector4 ToVect(Rectangle r)
    {
        return {r.x, r.y, r.width, r.height};
    }

    inline Rectangle ToRect(Vector4 v)
    {
        return {v.x, v.y, v.z, v.w};
    }

public:
    void main()
    {
        if (curr_item.rect == 0)
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                for (size_t i = 0; i < dragables_len; i++)
                {
                    Rectangle *c = dragables[i].rect;
                    assert(c != NULL && 'NULL WATCHABLE RECT');

                    if (CheckCollisionPointRec(GetMousePosition(), *c))
                    {
                        fprintf(stdout, "your clicking on %p!\n", c);
                        curr_item = dragables[i];
                    }
                }
            }
        }

        if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            curr_item = {0};
        }
        else if (curr_item.rect != 0)
        {

            Vector2 delta = GetMouseDelta();

            curr_item.rect->x += delta.x;
            curr_item.rect->y += delta.y;
        }
    }
} CLICK_DRAG;

int main(int argc, char **argv)
{
    int x = 100;
    int y = 50;
    PC.label = "PC";
    PC.pos.x = x;
    PC.pos.y = y;

    MAR.label = "MAR";
    MAR.pos.x = x;
    MAR.pos.y = y += 50;

    MDR.label = "MDR";
    MDR.pos.x = x;
    MDR.pos.y = y += 50;

    MX_MAR.label = "MAR";
    MX_MAR.pos.x = x;
    MX_MAR.pos.y = y += 50;

    InitWindow(800, 600, "Little Cpu");

    SetTargetFPS(30);
    while (!WindowShouldClose())
    {

        CLICK_DRAG.main();

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