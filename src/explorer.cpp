#include "explorer.h"
#include "raygui.h"
#include "raylib.h"
#include "style_catppuccin_mocha.h"
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

static const int INDENT = 20;

static std::vector<ExplorerItem> buildTree(fs::path path) {
  std::vector<ExplorerItem> items;
  for (const auto &entry : fs::directory_iterator(path)) {
    ExplorerItem item = {};
    item.name = entry.path().filename().string();
    if (entry.is_directory()) {
      item.type = ItemType::DIRECTORY;
      item.children = buildTree(entry.path());
      if (entry.path().has_parent_path()) {
        item.parent = entry.path().parent_path();
        item.isOpen = false;
      }
    } else {
      item.type = ItemType::FILE;
    }
    items.push_back(item);
  }
  return items;
}

void Explorer::scan() {
  fs::path currentPath(".");
  if (!fs::exists(currentPath)) {
    return;
  }
  this->items = buildTree(currentPath);
}

static int countItems(const std::vector<ExplorerItem> &items) {
  int count = 0;
  for (const auto &item : items) {
    count++;
    if (item.isOpen) {
      count += countItems(item.children);
    }
  }
  return count;
}

void Explorer::drawItems(std::vector<ExplorerItem> &items, float &x, float &y,
                         float panelLeft, float rowWidth) {
  int lineHeight = this->state->lineHeight;
  for (auto &item : items) {
    y += lineHeight;

    if (&item == this->selectedItem)
      DrawRectangleRec({panelLeft, y, rowWidth, (float)lineHeight},
                       GetColor(MOCHA_SURFACE1));

    if (GuiButton({x, y, panelLeft + rowWidth - x, (float)lineHeight},
                  item.name.c_str())) {
      this->selectedItem = &item;
      if (item.type == ItemType::DIRECTORY) {
        item.isOpen = !item.isOpen;
      }
    }
    if (!item.children.empty() && item.isOpen) {
      DrawLine((x + INDENT), (y + lineHeight), (x + INDENT),
               (y + (countItems(item.children) + 1) * lineHeight),
               GetColor(MOCHA_SURFACE1));
      x += INDENT;
      drawItems(item.children, x, y, panelLeft, rowWidth);
      x -= INDENT;
    }
  }
}

void Explorer::draw() {
  GuiSetStyle(BUTTON, BORDER_WIDTH, 0);
  GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
  GuiSetStyle(BUTTON, TEXT_PADDING, 8);
  GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, MOCHA_TRANSPARENT);
  GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, MOCHA_HOVER_BG);
  GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, MOCHA_PRESSED_BG);
  GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, MOCHA_TRANSPARENT);
  GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, MOCHA_TRANSPARENT);
  GuiSetStyle(BUTTON, BORDER_COLOR_PRESSED, MOCHA_TRANSPARENT);
  GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, MOCHA_TEXT);
  GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, MOCHA_TEXT);
  GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, MOCHA_TEXT);

  float contentHeight = countItems(items) * this->state->lineHeight;
  Rectangle panelBounds = {0, 0, 220, (float)GetScreenHeight()};
  Rectangle contentRect = {0, 0, 200, contentHeight};
  Rectangle view = {0, 0, 0, 0};

  GuiScrollPanel(panelBounds, NULL, contentRect, &scrollOffset, &view);

  BeginScissorMode((int)view.x, (int)view.y, (int)view.width, (int)view.height);
  float x = panelBounds.x + scrollOffset.x;
  float y = panelBounds.y + scrollOffset.y;
  drawItems(items, x, y, panelBounds.x, view.width);
  EndScissorMode();
}
