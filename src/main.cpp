#include <stdio.h>
#include <raylib.h>

/// @brief i_data[], o_data[], i_ld
struct
{
public:
    int x, y;
    const char *name;
    void draw()
    {
        DrawRectangle(x, y, 100, 32, WHITE);
        DrawText(name, x, y, 12, YELLOW);
    }
} PC;

int main(int argc, char **argv)
{
    PC.name = "PC";
    PC.x = 0;
    PC.y = 0;

    InitWindow(600, 400, "Little Cpu");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        PC.draw();
        DrawText("Hello world!", 50, 50, 12, WHITE);
        EndDrawing();
    }
    
    CloseWindow();
}