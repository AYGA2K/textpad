#include "explorer.h"
#include "raygui.h"
#include "raylib.h"
#include <vector>
void drawExplorer(const std::vector<ExplorerItem> &items, float &x, float &y) {
  int buttonWidth = 150;
  int buttonHeight = 30;
  int spacing = 2;
  for (size_t i = 0; i < items.size(); i++) {
    y += (buttonHeight + spacing);

    Rectangle buttonRect = {x, y, (float)buttonWidth, (float)buttonHeight};

    const auto &item = items[i];

    if (GuiButton(buttonRect, item.name.c_str())) {
      TraceLog(LOG_INFO, "Button '%s' clicked!", item.name.c_str());
    }

    if (!item.children.empty()) {
      x += 50;
      drawExplorer(item.children, x, y);
      x -= 50;
    }
  }
}
int main() {
  SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);
  InitWindow(1800, 720, "raygui - controls test suite");
  SetTargetFPS(60);

  Font fontBm = LoadFont("fonts/JetBrainsMono-Regular.ttf");
  GuiSetFont(fontBm);
  GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
  Explorer explorer;
  explorer.render();
  GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt({0, 0, 0, 0}));
  GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt({0, 0, 0, 0}));
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
    float explorerX = 0;
    float explorerY = 0;
    drawExplorer(explorer.items, explorerX, explorerY);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
