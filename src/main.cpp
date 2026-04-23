#include "explorer.h"
#include "raygui.h"
#include "raylib.h"
#include "style_catppuccin_mocha.h"

int main() {
  SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);
  InitWindow(1800, 720, "textpad");
  SetTargetFPS(60);

  GuiLoadStyleCatppuccinMocha();
  Font fontBm = LoadFont("fonts/JetBrainsMono-Regular.ttf");
  GuiSetFont(fontBm);
  GuiSetStyle(DEFAULT, TEXT_SIZE, 16);

  Explorer explorer;
  explorer.scan();

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(GetColor(MOCHA_BASE));
    explorer.draw();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
