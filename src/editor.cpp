#include "editor.h"
#include "raygui.h"
#include "raylib.h"
#include "style_catppuccin_mocha.h"
#include <string>

static const int EXPLORER_WIDTH = 220;

void Editor::draw() {
  lastKey = GetKeyPressed();
  TraceLog(2, "Key Pressed: %s", std::to_string(lastKey).c_str());

  Rectangle area = {(float)EXPLORER_WIDTH, 0,
                    (float)(GetScreenWidth() - EXPLORER_WIDTH),
                    (float)GetScreenHeight()};
  DrawRectangleRec(area, GetColor(MOCHA_BASE));
  DrawRectangleLinesEx(area, 1, GetColor(MOCHA_SURFACE1));
  if (this->isFocused) {
    Vector2 vectStart = {float(this->cursor.x), float(this->cursor.y)};
    Vector2 vectEnd = {float(this->cursor.x), float(this->cursor.y + state->fontSize)};


    DrawLineEx(vectStart, vectEnd, 3, GetColor(MOCHA_TEXT));
  }
}
