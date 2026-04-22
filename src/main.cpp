#include "raygui.h"
#include "raylib.h"
int main() {
  SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);
  InitWindow(1800, 720, "raygui - controls test suite");
  SetTargetFPS(60);

  bool showMessageBox = false;
  Font fontBm = LoadFont("/usr/share/fonts/noto/NotoSans-Regular.ttf");
  GuiSetFont(fontBm);
  GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    if (GuiButton({24, 24, 200, 30}, "#191#You want an editor"))
      showMessageBox = true;

    if (showMessageBox) {
      int result = GuiMessageBox({86, 70, 250, 100}, "#191#Message Box",
                                 "Are you sure", "Yes;Yes");

      if (result >= 0)
        showMessageBox = false;
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
