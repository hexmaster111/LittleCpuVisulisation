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
    const int w = 100;
    const int h = 32;
    const int fontsize = 18;

    const char *label;
    float rotation;
    Rectangle pos = {0, 0, w, h};

    void draw()
    {
        rlPushMatrix();
        {
            rlTranslatef(pos.x, pos.y, 0.0f);
            rlRotatef(rotation, 0, 0, 1);
            rlTranslatef(-pos.x - w / 2, -pos.y, 0.0f);
            DrawRectangle(pos.x, pos.y, w, h, WHITE);
            DrawText(label, pos.x + (w / 2) - (MeasureText(label, fontsize) / 2), pos.y + 8, fontsize, BLACK);
        }
        rlPopMatrix();
    }
} PC, MAR, MDR;

struct MUX
{
    const int triw = 25 / 2;
    const int rectw = 100;
    const int h = 32;
    const int fontsize = 18;

    Rectangle pos = {0, 0, rectw + triw * 2, h};

    float rotation;
    const char *label;

    void draw()
    {
        rlPushMatrix();
        {
            rlTranslatef(pos.x, pos.y, 0.0f);
            rlRotatef(rotation, 0, 0, 1);
            rlTranslatef(-pos.x - rectw / 2, -pos.y, 0.0f);

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
            rlPopMatrix();
        }
    }
} MX_MAR, MX_PC, MX_ACC;

struct WIRE
{
};

struct BLOCK
{
    Rectangle *rect;
    float *rotation;
};

const int dragables_len = 6;
BLOCK dragables[dragables_len] = {
    {&MX_MAR.pos, &MX_MAR.rotation},
    {&MX_PC.pos, &MX_PC.rotation},
    {&MX_ACC.pos, &MX_ACC.rotation},
    {&PC.pos, &PC.rotation},
    {&MAR.pos, &MAR.rotation},
    {&MDR.pos, &MDR.rotation},

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

            if (IsKeyDown(KEY_R))
            {
                *curr_item.rotation += delta.x;
                return;
            }

            if (IsKeyReleased(KEY_R))
            {
                float currRot = *curr_item.rotation;

                curr_item = {0};
                return;
            }

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
    MX_MAR.rotation = 0;

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